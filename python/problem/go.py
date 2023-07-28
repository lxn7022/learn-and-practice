# encoding: utf-8
"""
背景介绍
1.围棋棋盘由n行和n列构成，形成n2个交叉点，简称为“点”;
2.围棋棋子分黑白两色，黑白棋子轮流交替下子于棋盘中的空点上;
3一个棋子a在棋盘上，与它直线相邻(正上方/正下方/正左方/正右方)的点:31如果为空点，则为棋子a的气;
3.2如果为同色棋子b，则a和b连接成一块不可分割的整体(b若还连接同色棋子c，则c也都
在这个不可分割的整体里)，整体中单个棋子的气就是整体的气;33如果为异色棋子d，则棋子a在此处没有气;
4.如果棋子或多个同色棋子组成的整体失去所有的气，则该棋子或整体称为“无气子”，无气子不应该再留在棋盘上，将无气子清理出棋盘称为“提子”，两种情况可提子:41下子后，对方棋子无气，立即提取对方无气子;
4.2下子后，双方棋子都无气，立即提取对方无气子;
5.若某点下子后，该子或该子所在整体成无气子，且对方未出现无气子，则该点不可下子，该点称为禁着点。

算法要求
现给定n行n列的围棋棋盘残局和即将下子的黑子下子点p，请计算下子后下一轮白子下子前的棋盘残局并返回。
"""


import pytest
N = 6
BLACK = 1
WHITE = -1
NULL = 0


class Go:
    def __init__(self) -> None:
        self.isalive_flag = 0
        self.checkerboard_data = [[0 for i in range(N)] for j in range(N)]
        self.visit = [[0 for i in range(N)] for j in range(N)]

    def __str__(self):
        ret = "Go.checkboard:"
        for m in self.checkerboard_data:
            ret += "\n"
            ret += str(m)
        return ret

    # 设置初始局
    def set_matrix(self, matrix):
        if len(matrix) != N:
            return
        for m in matrix:
            if len(m) != N:
                return
        self.checkerboard_data = matrix

    # 下子
    def set_point(self, x, y, player):
        if x < 0 or x > N-1 or y < 0 or y > N-1:
            return
        if player not in (WHITE, BLACK, NULL):
            return
        self.checkerboard_data[x][y] = player

    # 清空搜索记录
    def clear_visit(self):
        self.visit = [[0 for i in range(N)] for j in range(8)]
        self.isalive_flag = 0

    # 有无“气”的判断，有气返回1，无气返回0
    def is_alive(self, x, y):
        isalive = 1  # 用于返回
        # 清空搜索记录
        self.clear_visit()
        # 执行深度优先搜索
        self.DFS(x, y)
        # 有“气”标志为0,则返回0,否则为1
        if self.isalive_flag == 0:
            isalive = 0
        # 再次清空搜索记录
        self.clear_visit()
        return isalive

    def DFS(self, x, y):
        self.visit[x][y] = 1  # 表示此点已经搜索过
        directions = [[x - 1, y], [x + 1, y],
                      [x, y - 1], [x, y + 1]]  # 定义上下左右四个方向
        for dx, dy in directions:
            if dx < 0 or dx > N-1 or dy < 0 or dy > N-1:
                continue  # 如果是边框，跳过此方向
            elif self.visit[dx][dy] == 0:  # 判断是否此点搜索过
                if self.checkerboard_data[dx][dy] == 0:
                    self.isalive_flag = 1
                    return  # 此点为空位置，即原棋子有气，停止搜索
                elif self.checkerboard_data[dx][dy] == - self.checkerboard_data[x][y]:
                    continue  # 对方棋子，跳过此方向
                elif self.checkerboard_data[dx][dy] == self.checkerboard_data[x][y]:
                    self.DFS(dx, dy)  # 己方棋子，递归执行
        # 以上条件都不满足,即所有路径都为死路,该棋子无“气”,停止搜索
        return

    # 提掉没有“气”的子
    def take_out(self, player):
        token_list = []  # “死亡”名单
        # 遍历整个棋盘
        for i in range(N):
            for j in range(N):
                # 若当前位置是空,则直接跳过
                if self.checkerboard_data[i][j] == 0:
                    continue
                # 判断该棋子有无“气”(只判断对方棋子)
                elif self.checkerboard_data[i][j] == -player and self.is_alive(i, j) == 0:
                    # 将无“气”的棋子加入“死亡”名单
                    token_list.append([i, j])

        # 若名单不为空,则提去名单中的所有棋子(仅对方棋子)
        if len(token_list) != 0:
            for i, j in token_list:
                self.checkerboard_data[i][j] = 0


def test_Go():
    go = Go()
    matrix1 = [[0, 0, 0, 0, 0, 0],
               [0, 0, 1, 0, 0, 0],
               [0, 1, -1, 1, 0, 0],
               [0, 0, 0, 0, 0, 0],
               [0, 0, 0, 0, 0, 0],
               [0, 0, 0, 0, 0, 0]]
    matrix2 = [[0, 0, 0, 0, 0, 0],
               [1, 0, 0, 0, 0, 0],
               [-1, 0, 0, 0, 0, 0],
               [-1, 1, 0, 0, 0, 0],
               [1, 0, 0, 0, 0, 0],
               [0, 0, 0, 0, 0, 0]]
    matrix3 = [[0, 0, 0, 0, 0, 0],
               [1, 0, 1, 0, 0, 0],
               [-1, -1, 1, 0, 0, 0],
               [-1, -1, 1, 0, 0, 0],
               [1, 1, 0, 0, 0, 0],
               [0, 0, 0, 0, 0, 0]]

    def _move(matrix, x, y, player):
        print("#-------------------------")
        go.set_matrix(matrix)
        print(go)
        go.set_point(x, y, BLACK)
        go.take_out(BLACK)
        print("#-----")
        print(go)

    _move(matrix1, 3, 2, BLACK)
    _move(matrix2, 2, 1, BLACK)
    _move(matrix3, 1, 1, BLACK)


if __name__ == '__main__':
    pytest.main(["-v", "-s", "go.py"])
