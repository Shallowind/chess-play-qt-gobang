import numpy as np
import copy


def softmax(x):
    # 计算softmax值，输入是一个向量，转换成概率分布
    probs = np.exp(x - np.max(x))
    probs /= np.sum(probs)
    return probs


class TreeNode(object):
    # MCTS 树中的一个节点，每个节点都有自己的价值 Q、先验概率 P 和访问次数

    def __init__(self, parent, prior_p):
        self._parent = parent
        self._children = {}
        # 访问次数
        self._n_visits = 0
        # 价值 Q
        self._Q = 0
        # 奖励 u
        self._u = 0
        # 先验概率 P
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
        # 如果子节点为空，说明是叶节点，返回True
        return self._children == {}

    def is_root(self):

        # 如果父节点为空，说明是根节点，返回True
        return self._parent is None


class MCTS(object):
    # 蒙特卡洛树搜索的实现

    def __init__(self, policy_value_fn, c_puct=5, n_playout=10000):
        self._root = TreeNode(None, 1.0)
        self._policy = policy_value_fn
        self._c_puct = c_puct
        self._n_playout = n_playout

    def _playout(self, state):
        """模拟一次完整的蒙特卡洛树搜索，从根节点到叶节点，然后从叶节点返回评估值。
        """
        node = self._root
        while (1):
            if node.is_leaf():
                break
            # 贪婪地选择下一步。
            action, node = node.select(self._c_puct)
            state.do_move(action)
        action_probs, leaf_value = self._policy(state)
        leaf_value = leaf_value.cpu().numpy()

        end, winner = state.game_end()
        if not end:
            node.expand(action_probs)
        else:
            if winner == -1:  # tie
                leaf_value = 0.0
            else:
                leaf_value = (
                    1.0 if winner == state.get_current_player() else -1.0
                )

        # 更新本次遍历节点的值和访问次数。
        node.update_recursive(-leaf_value)

    def get_move_probs(self, state, temp=1e-3):
        # 进行n_playout次蒙特卡洛树搜索，返回动作和概率。
        for n in range(self._n_playout):
            state_copy = copy.deepcopy(state)
            self._playout(state_copy)

        # 根据访问次数计算动作概率。
        act_visits = [(act, node._n_visits)
                      for act, node in self._root._children.items()]
        acts, visits = zip(*act_visits)
        act_probs = softmax(1.0/temp * np.log(np.array(visits) + 1e-10))

        return acts, act_probs

    def update_with_move(self, last_move):
        # 更新根节点，保留子树。
        if last_move in self._root._children:
            self._root = self._root._children[last_move]
            self._root._parent = None
        else:
            self._root = TreeNode(None, 1.0)

    def __str__(self):
        return "MCTS"


class MCTSPlayer(object):
    # 蒙特卡洛树搜索玩家，用于AlphaGo Zero。

    def __init__(self, policy_value_function,
                 c_puct=5, n_playout=2000, is_selfplay=0):
        self.mcts = MCTS(policy_value_function, c_puct, n_playout)
        self._is_selfplay = is_selfplay

    def set_player_ind(self, p):
        self.player = p

    def reset_player(self):
        self.mcts.update_with_move(-1)

    def get_action(self, board, temp=1e-3, return_prob=0):
        sensible_moves = board.availables
        # MCTS 返回的 pi 向量
        move_probs = np.zeros(board.width*board.height)
        if len(sensible_moves) > 0:
            acts, probs = self.mcts.get_move_probs(board, temp)
            move_probs[list(acts)] = probs
            if self._is_selfplay:
                # 添加狄利克雷噪声进行探索（自我对弈训练）
                move = np.random.choice(
                    acts,
                    p=0.75*probs + 0.25 *
                    np.random.dirichlet(0.2*np.ones(len(probs)))
                )
                # 更新根节点并重用搜索树
                self.mcts.update_with_move(move)
            else:
                # 默认temp=1e-3，几乎等价，选择概率最高的着法
                move = np.random.choice(acts, p=probs)
                # 重置根节点
                self.mcts.update_with_move(-1)

            if return_prob:
                return move, move_probs
            else:
                return move
        else:
            print("WARNING: the board is full")

    def __str__(self):
        return "MCTS {}".format(self.player)
