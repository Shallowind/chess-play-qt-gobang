import numpy as np
import copy
from operator import itemgetter


def rollout_policy_fn(board):
    # 随机选择一个动作
    action_probs = np.random.rand(len(board.availables))
    return zip(board.availables, action_probs)


def policy_value_fn(board):

    # 一个函数，输入一个状态，输出一个列表（动作，概率）元组和一个状态的分数

    # 返回均匀概率和0分数的纯MCTS
    action_probs = np.ones(len(board.availables))/len(board.availables)
    return zip(board.availables, action_probs), 0


class TreeNode(object):
    # MCTS 树中的一个节点，每个节点都有自己的价值 Q、先验概率 P 和访问次数
    def __init__(self, parent, prior_p):
        self._parent = parent
        self._children = {}
        self._n_visits = 0
        self._Q = 0
        self._u = 0
        self._P = prior_p

    def expand(self, action_priors):
        """
            初始化树节点，需要知道父节点和先验概率
        """
        for action, prob in action_priors:
            if action not in self._children:
                self._children[action] = TreeNode(self, prob)

    def select(self, c_puct):
        """
        选择最大动作值 Q 加上奖励 u(P) 的子节点中的动作。
        """
        return max(self._children.items(),
                   key=lambda act_node: act_node[1].get_value(c_puct))

    def update(self, leaf_value):
        """
            从叶节点评估更新节点值，叶节点的值是从当前玩家的角度评估的子树值
        """
        self._n_visits += 1
        self._Q += 1.0*(leaf_value - self._Q) / self._n_visits

    def update_recursive(self, leaf_value):
        """
        递归update函数更新每个节点的值，优先更新父节点
        """
        if self._parent:
            self._parent.update_recursive(-leaf_value)
        self.update(leaf_value)

    def get_value(self, c_puct):
        # 计算节点值，是叶节点评估 Q 和先验概率 P 的组合，奖励 u 是先验概率 P 与访问次数 n 的比值
        # UCT：Q + u(P) = Q + c_puct * P * sqrt (N) / (1 + N)
        self._u = (c_puct * self._P *
                   np.sqrt(self._parent._n_visits) / (1 + self._n_visits))
        return self._Q + self._u

    def is_leaf(self):
        return self._children == {}

    def is_root(self):
        return self._parent is None


class MCTS(object):
    """A simple implementation of Monte Carlo Tree Search."""

    def __init__(self, policy_value_fn, c_puct=5, n_playout=10000):
        """

            一个列表（动作，概率）元组和得分[-1,1]
            （即期望值的结束游戏得分从当前玩家的角度）为当前玩家。

            一个数字（0，inf），控制探索的速度收敛到最大值策略。 一个更高的值意味着更多地依赖于先前的值。
        """
        # 根节点
        self._root = TreeNode(None, 1.0)
        # 策略函数
        self._policy = policy_value_fn
        # 探索参数
        self._c_puct = c_puct
        # 模拟次数
        self._n_playout = n_playout

    def _playout(self, state):
        """
        运行一个单独的模拟，从根到叶子，得到一个值
        在叶子和通过其父节点    传播回来。
        状态是就地修改的，所以必须提供一个副本。
        """
        node = self._root
        while (1):
            if node.is_leaf():
                break
            # 贪婪地选择下一步。
            action, node = node.select(self._c_puct)
            state.do_move(action)

        action_probs, _ = self._policy(state)
        # 检查游戏结束
        end, winner = state.game_end()
        if not end:
            node.expand(action_probs)
        # 通过随机 rollout 评估叶节点
        leaf_value = self._evaluate_rollout(state)
        # 更新本次遍历节点的值和访问次数。
        node.update_recursive(-leaf_value)

    def _evaluate_rollout(self, state, limit=1000):
        """使用“rollout_policy_fn”玩游戏到结束，不使用“self._policy”。
        """
        player = state.get_current_player()
        for i in range(limit):
            end, winner = state.game_end()
            if end:
                break
            action_probs = rollout_policy_fn(state)
            max_action = max(action_probs, key=itemgetter(1))[0]
            state.do_move(max_action)
        else:
            print("WARNING: rollout reached move limit")
        if winner == -1:  # 平局
            return 0
        else:
            return 1 if winner == player else -1

    def get_move(self, state):
        """
        获得最多访问的动作
        """

        # 进行n次模拟
        for n in range(self._n_playout):
            state_copy = copy.deepcopy(state)
            # 传入当前棋盘状态模拟进行
            self._playout(state_copy)

        # 选择访问最多的动作
        return max(self._root._children.items(),
                   key=lambda act_node: act_node[1]._n_visits)[0]

    def update_with_move(self, last_move):
        """
        向前迈出一步，保留以前的数据
        """
        if last_move in self._root._children:
            self._root = self._root._children[last_move]
            self._root._parent = None
        else:
            self._root = TreeNode(None, 1.0)

    def __str__(self):
        return "MCTS"


class MCTSPlayer(object):
    """基于MCTS的AI玩家"""

    def __init__(self, c_puct=5, n_playout=2000):
        self.mcts = MCTS(policy_value_fn, c_puct, n_playout)

    def set_player_ind(self, p):
        self.player = p

    def reset_player(self):
        self.mcts.update_with_move(-1)

    def get_action(self, board):
        sensible_moves = board.availables
        if len(sensible_moves) > 0:

            # 如果有合理的移动，使用MCTS选择一个
            move = self.mcts.get_move(board)
            # 更新根节点
            self.mcts.update_with_move(-1)

            return move
        else:
            print("WARNING: the board is full")

    def __str__(self):
        return "MCTS {}".format(self.player)
