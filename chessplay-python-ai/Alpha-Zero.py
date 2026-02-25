from __future__ import print_function
import pickle
import tkinter
import tkinter.ttk
from mcts_pure import MCTSPlayer as MCTS_Pure
from mcts_alphaZero import MCTSPlayer
from policy_value_net_numpy import PolicyValueNetNumpy
from policy_value_net_pytorch import PolicyValueNet
import numpy as np
import os
import tkinter.messagebox as messagebox

import ctypes


class luo(object):
    x1 = 0
    y1 = 0
    x2 = 0
    y2 = 0
    win = 0
    start = 0
    # 数组记录棋盘
    chessboard = np.zeros((11, 11))
    human_color = "white"
    ai_color = "black"


luozi = luo()


class Board(object):

    def __init__(self, **kwargs):
        self.width = int(kwargs.get('width', 8))
        self.height = int(kwargs.get('height', 8))
        self.states = {}
        # 5连子胜利
        self.n_in_row = int(kwargs.get('n_in_row', 5))
        self.players = [1, 2]

    def init_board(self, start_player=0):
        if self.width < self.n_in_row or self.height < self.n_in_row:
            raise Exception('board width and height can not be '
                            'less than {}'.format(self.n_in_row))
        self.current_player = self.players[start_player]
        # key:move, value:player
        self.availables = list(range(self.width * self.height))
        self.states = {}
        self.last_move = -1

    def move_to_location(self, move):
        """将move转换为坐标形式"""
        h = move // self.width
        w = move % self.width
        return [h, w]

    def location_to_move(self, location):
        if len(location) != 2:
            return -1
        h = location[0]
        w = location[1]
        move = h * self.width + w
        if move not in range(self.width * self.height):
            return -1
        return move

    def current_state(self):
        """返回当前棋盘状态
        """

        square_state = np.zeros((4, self.width, self.height))
        if self.states:
            moves, players = np.array(list(zip(*self.states.items())))
            move_curr = moves[players == self.current_player]
            move_oppo = moves[players != self.current_player]
            square_state[0][move_curr // self.width,
                            move_curr % self.height] = 1.0
            square_state[1][move_oppo // self.width,
                            move_oppo % self.height] = 1.0
            square_state[2][self.last_move // self.width,
                            self.last_move % self.height] = 1.0
        if len(self.states) % 2 == 0:
            square_state[3][:, :] = 1.0
        return square_state[:, ::-1, :]

    def do_move(self, move):
        self.states[move] = self.current_player
        self.availables.remove(move)
        self.current_player = (
            self.players[0] if self.current_player == self.players[1]
            else self.players[1]
        )
        self.last_move = move

    def has_a_winner(self):
        width = self.width
        height = self.height
        states = self.states
        n = self.n_in_row

        moved = list(set(range(width * height)) - set(self.availables))
        if len(moved) < self.n_in_row * 2-1:
            return False, -1

        for m in moved:
            h = m // width
            w = m % width
            player = states[m]

            if (w in range(width - n + 1) and
                    len(set(states.get(i, -1) for i in range(m, m + n))) == 1):
                return True, player

            if (h in range(height - n + 1) and
                    len(set(states.get(i, -1) for i in range(m, m + n * width, width))) == 1):
                return True, player

            if (w in range(width - n + 1) and h in range(height - n + 1) and
                    len(set(states.get(i, -1) for i in range(m, m + n * (width + 1), width + 1))) == 1):
                return True, player

            if (w in range(n - 1, width) and h in range(height - n + 1) and
                    len(set(states.get(i, -1) for i in range(m, m + n * (width - 1), width - 1))) == 1):
                return True, player

        return False, -1

    def game_end(self):

        win, winner = self.has_a_winner()
        if win:
            return True, winner
        elif not len(self.availables):
            return True, -1
        return False, -1

    def get_current_player(self):
        return self.current_player


class Game(object):
    """game server"""

    def __init__(self, board, **kwargs):
        self.board = board

    def graphic(self, board, player1, player2):
        """Draw the board and show game info"""
        width = board.width
        height = board.height

        if board.last_move != -1:
            last_move_loc = board.move_to_location(board.last_move)
            luozi.x1 = last_move_loc[0]
            luozi.y1 = last_move_loc[1]

    def ai_move(self, player):
        move = player.get_action(self.board)
        self.board.do_move(move)
        end, winner = self.board.game_end()
        self.graphic(self.board, human, mcts_player)
        if end:
            if winner != -1:
                if winner == 1:
                    luozi.win = 1
                elif winner == 2:
                    luozi.win = 2
            else:
                luozi.win = 3
        return winner

    def start_play(self, player1, player2, start_player=0, is_shown=1):
        """start a game between two players"""
        if start_player not in (0, 1):
            raise Exception('start_player should be either 0 (player1 first) '
                            'or 1 (player2 first)')
        self.board.init_board(start_player)
        p1, p2 = self.board.players
        player1.set_player_ind(p1)
        player2.set_player_ind(p2)
        players = {p1: player1, p2: player2}
        if is_shown:
            self.graphic(self.board, player1.player, player2.player)


class Human(object):
    """
    human player
    """

    def __init__(self):
        self.player = None

    def set_player_ind(self, p):
        self.player = p

    def get_action(self, board):
        while True:
            try:
                location = [luozi.x2, luozi.y2]
                move = board.location_to_move(location)
            except Exception as e:
                move = -1
            if move != -1 and move in board.availables:
                return move

    def __str__(self):
        return "Human {}".format(self.player)


n = 5
width, height = 11, 11
model_file = 'best_policy.model'
try:
    board = Board(width=width, height=height, n_in_row=n)
    game = Game(board)

    best_policy = PolicyValueNet(width, height, model_file)
    mcts_player = MCTSPlayer(
        best_policy.policy_value_fn, c_puct=5, n_playout=400)

    human = Human()


except KeyboardInterrupt:
    print('\n\rquit')


def start_play_game():
    Text.text.config(text="游戏开始")
    game.start_play(human, mcts_player, start_player=1, is_shown=1)


def draw_board(canvas):

    for i in range(11):
        canvas.create_line(40, 40 + i * 80, 840, 40 + i * 80)  # 绘制横线
        canvas.create_line(40 + i * 80, 40, 40 + i * 80, 840)  # 绘制竖线


def place_piece(canvas, x, y, color):
    radius = 30
    canvas.create_oval(40 + x * 80 - radius, 40 + y * 80 - radius,
                       40 + x * 80 + radius, 40 + y * 80 + radius,
                       fill=color)  # 绘制棋子
    canvas.update()


def delete_piece(canvas):
    canvas.create_rectangle(0, 0, 4000, 4000, fill='#D2B48C')
    canvas.create_rectangle(40, 40, 840, 840, fill='#FFE5B4')
    draw_board(canvas)


def win():
    if luozi.win == 1:
        Text.text.config(text="你赢了！")
    elif luozi.win == 2:
        Text.text.config(text="你输了...")
    elif luozi.win == 3:
        Text.text.config(text="平局")


def on_mouse_release(event):
    if luozi.win != 0:
        return
    x = (event.x - 40 + 40) // 80  # 加上一个偏移量进行修正
    y = (event.y - 40 + 40) // 80
    if x < 0 or x >= 11 or y < 0 or y >= 11 or luozi.chessboard[x][y] != 0 or luozi.start == 0:
        return
    luozi.x2 = x
    luozi.y2 = y
    place_piece(canvas, luozi.x2, luozi.y2, luozi.human_color)


    Text.text.config(text="AI正在思考...")

    luozi.chessboard[luozi.x2][luozi.y2] = 2
    canvas.unbind("<ButtonRelease-1>")  # 解绑鼠标点击事件
    window.update()
    game.ai_move(human)
    win()
    if luozi.win != 0:
        return
    ai_move()
    win()


def ai_move():
    game.ai_move(mcts_player)
    place_piece(canvas, luozi.x1, luozi.y1, luozi.ai_color)

    Text.text.config(text="轮到你了")
    luozi.chessboard[luozi.x1][luozi.y1] = 1
    canvas.bind("<ButtonRelease-1>", on_mouse_release)  # 绑定鼠标点击事件


# 创建窗口和画布
window = tkinter.Tk()
# 告诉操作系统使用程序自身的dpi适配
ctypes.windll.shcore.SetProcessDpiAwareness(1)
# 获取屏幕的缩放因子
ScaleFactor = ctypes.windll.shcore.GetScaleFactorForDevice(0)
# 设置程序缩放
window.tk.call('tk', 'scaling', ScaleFactor/100)
# 获取屏幕宽度和高度
screen_width = window.winfo_screenwidth()
screen_height = window.winfo_screenheight()

# 计算窗口左上角的坐标
x = (screen_width - 880) // 2 + 550
y = (screen_height - 950) // 2 + 300

# 设置窗口位置和大小
window.geometry('880x950+{}+{}'.format(x, y))


window.title("五子棋")
canvas = tkinter.Canvas(window, width=880, height=950, highlightthickness=0)
canvas.pack()
# 背景改为浅棕色
canvas.create_rectangle(0, 0, 4000, 4000, fill='#D2B48C')
# 棋盘区域颜色变浅
canvas.create_rectangle(40, 40, 840, 840, fill='#FFE5B4')
# 设置窗口大小不可变
window.resizable(0, 0)

# 绘制棋盘
draw_board(canvas)

# 创建按钮，点击按钮开始游戏


def start_game():
    # 清空棋盘
    for i in range(11):
        for j in range(11):
            luozi.chessboard[i][j] = 0

    delete_piece(canvas)
    luozi.win = 0
    draw_board(canvas)
    Text.text.config(text="请选择执棋颜色")
    luozi.start = 0

    # 弹窗选择
    result = messagebox.askquestion(
        "选择棋子",
        "是否执黑棋？\n\n是：你先手（黑棋）\n否：AI先手（黑棋）"
    )

    if result == "yes":
        # 玩家执黑，先手
        luozi.human_color = "black"
        luozi.ai_color = "white"
        start_player = 0   # human 先
    else:
        # 玩家执白，AI先手
        luozi.human_color = "white"
        luozi.ai_color = "black"
        start_player = 1   # AI 先

    button.config(text="重新开始")
    luozi.start = 1

    # 开始对局
    game.start_play(human, mcts_player, start_player=start_player, is_shown=1)

    # 如果 AI 先手，立刻下棋
    if start_player == 1:
        Text.text.config(text="AI正在思考...")
        window.update()
        ai_move()
    else:
        Text.text.config(text="轮到你了")



button_style = tkinter.ttk.Style()
button_style.configure('GameButton.TButton', font=('黑体', 13))

button = tkinter.ttk.Button(window, text="开始游戏", command=start_game,
                            width=16, padding=(10, 10), style='GameButton.TButton')
button.place(x=45, y=880)


# 创建文本框，显示游戏结果
class Text(object):
    text = tkinter.ttk.Label(window, text="请开始游戏(•ᴗ•)", font=(
        "楷体", 23), width=25, anchor='center')
    text.configure(background='#FFF8DC', foreground='#000000')

    text.place(x=320, y=883)


# 绑定鼠标释放事件
canvas.bind("<ButtonRelease-1>", on_mouse_release)


window.mainloop()
