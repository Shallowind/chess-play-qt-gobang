import os
import socket
import json
import numpy as np

from mcts_alphaZero import MCTSPlayer
from policy_value_net_pytorch import PolicyValueNet

HOST = '127.0.0.1'
PORT = 5000

BOARD_SIZE = 11
N_IN_ROW = 5
MODEL_FILE = 'best_policy.model'

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
        if len(moved) < self.n_in_row * 2 - 1:
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


def build_board_from_json(board_json, ai_player):
    board = Board(width=BOARD_SIZE, height=BOARD_SIZE, n_in_row=N_IN_ROW)
    board.init_board(start_player=0)

    for i in range(BOARD_SIZE):
        for j in range(BOARD_SIZE):
            if board_json[i][j] == 1:
                move = board.location_to_move([i, j])
                board.states[move] = 1
                board.availables.remove(move)
            elif board_json[i][j] == 2:
                move = board.location_to_move([i, j])
                board.states[move] = 2
                board.availables.remove(move)

    # 核心修正
    board.current_player = ai_player
    return board



def main():
    print("Loading AlphaZero model...")
    policy_net = PolicyValueNet(BOARD_SIZE, BOARD_SIZE, MODEL_FILE)
    ai_player = MCTSPlayer(
        policy_net.policy_value_fn,
        c_puct=5,
        n_playout=400
    )
    print("AlphaZero ready.")

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((HOST, PORT))
    server.listen(1)

    print(f"Listening on {HOST}:{PORT}")

    while True:
        print("Waiting for Qt client...")
        conn, addr = server.accept()
        print("Connected by", addr)

        buffer = b""

        try:
            while True:
                data = conn.recv(4096)
                if not data:
                    print("Qt disconnected")
                    break

                buffer += data
                while b'\n' in buffer:
                    line, buffer = buffer.split(b'\n', 1)
                    request = json.loads(line.decode())

                    board_json = request["board"]
                    ai_player_ = request["ai_player"]
                    board = build_board_from_json(board_json, ai_player_)

                    move = ai_player.get_action(board)
                    x, y = board.move_to_location(move)

                    response = json.dumps({
                        "x": int(x),
                        "y": int(y)
                    }) + "\n"

                    conn.sendall(response.encode())

        except Exception as e:
            print("Error:", e)

        finally:
            conn.close()
            print("Connection closed, waiting for new client...")


if __name__ == "__main__":
    main()
