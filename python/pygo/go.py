# 游戏名称：Go Demo
# 描述：围棋游戏
# 作者：吃草的哥哥哥斯拉
# 功能说明
# 1.下子：鼠标点击
# 2.重启游戏：按下键盘r键或回车键
# 3.放弃下子：按下键盘s键
# 4.退出游戏：按下esc键或点击关闭窗口
# 代码链接：
# https://blog.csdn.net/weixin_41244698/article/details/108188243

import sys
import pygame
from pygame.locals import *
# 启动pygame
pygame.init()
# 创建窗口
screen = pygame.display.set_mode((600, 600))
# 设置标题
pygame.display.set_caption("Go Demo")
# 设定字体
font1 = pygame.font.SysFont('SimHei', 20)
font2 = pygame.font.SysFont('arial', 35)
# 设置颜色
background_color = 150, 180, 150
black = 0, 0, 0
white = 255, 255, 255
circle_color = 0, 0, 0
lines_color = 100, 0, 0
text_color = 50, 0, 0

# 在pygame屏幕上打印文字


def print_text(font, x, y, text, color=(0, 0, 0)):
    imgText = font.render(text, True, color)
    screen.blit(imgText, (x, y))


# 记录鼠标事件
mouse_x = mouse_y = 0
mouse_up = 0
mouse_up_x = mouse_up_y = 0

# 定义围棋类
# =========================================================================
# 类名: Go
# 描述: 9x9围棋游戏
# 可用方法:
# 1) 主游戏方法: play()
#    描述: 围棋主游戏的运行,写在pygame的主循环中
# 2) 下子方法: make_a_move(x, y)
#    描述: x,y分别填入鼠标弹起的坐标mouse_up_x,mouse_up_y即可完成下子
# 3) 获取当前鼠标位置方法: get_mouse_current_position(x, y)
#    描述: x,y分别填入鼠标当前的坐标mouse_x,mouse_y,棋子可跟随鼠标移动
# 4) 重启游戏方法: restart_game()
#    描述: 使用此方法重启游戏(清空棋盘,重置当前玩家)
# 5) 悔棋方法(未实现): take_back_a_move()
#    描述: 使用此方法可悔棋,即全局回退到上一步(最多回退五步)
# 6) 转换玩家: switch_play()
#    描述: 使用此方法强制切换当前玩家
# 已实现功能:
#    下子,切换玩家,提去无“气”的子,防止自杀
# 未实现功能:
#    未实现全局同形再现的判断,未实现点目和胜负判断
#    未实现悔棋功能
#    不能调整棋盘路数,不能调整窗口大小
# =========================================================================


class Go:
    def __init__(self):
        # -----------------以下为游戏部分数据域--------------------
        # 用二维列表表示存储棋盘数据,黑子为-1,白子为1,无子为0
        self.__checkerboard_data = [[0 for i in range(9)] for j in range(9)]
        # 当前玩家标志,黑为-1,白为1
        self.__player_flag = -1
        # 游戏结束标志
        self.__game_over = 0
        # 记录鼠标位置
        self.__mouse_x = 0
        self.__mouse_y = 0
        # 自杀标志
        self.__suicide_flag = 0
        # 栈(保存前五步棋局)
        self.__stack = []
        # 全局同形再现标志(暂无功能)
        self.__repeat_flag = 0

    # ------------------以下为搜索部分数据域-------------------
        # 存储已搜索过的位置,防止重复搜索
        self.__visit = [[0 for i in range(9)] for j in range(9)]
        # 是否有“气”标志
        self.__isalive_flag = 0

    # -------------------以下为游戏方法--------------------
    # 绘制棋盘(私有方法)
    def __draw_checker(self):
        # 绘制九路棋盘
        color = lines_color
        line_width = 1
        rect_pos = 100, 100, 400, 400
        # 绘制边框
        pygame.draw.rect(screen, color, rect_pos, line_width * 2)
        # 绘制内线条
        for i in range(7):
            pygame.draw.line(screen, color, (100, 100 + i * 50 + 50),
                             (500, 100 + i * 50 + 50), line_width)
        for i in range(7):
            pygame.draw.line(screen, color, (100 + i * 50 + 50, 100),
                             (100 + i * 50 + 50, 500), line_width)
        # 绘制“天元”和“星”
        positions = [[300, 300], [200, 200], [
            200, 400], [400, 200], [400, 400]]
        for pos in positions:
            pygame.draw.circle(screen, color, pos, 5, 0)

    # 获取鼠标当前位置
    def get_mouse_current_position(self, x, y):
        self.__mouse_x = x
        self.__mouse_y = y

    # 棋子跟随鼠标移动(私有方法)
    def __chess_follow(self):
        pos = self.__mouse_x, self.__mouse_y
        if self.__player_flag == -1:
            color = black
        elif self.__player_flag == 1:
            color = white
        # 棋子填充
        pygame.draw.circle(screen, color, pos, 19, 0)
        # 棋子边框
        pygame.draw.circle(screen, circle_color, pos, 20, 2)

    # 切换玩家
    def switch_player(self):
        self.__player_flag = - self.__player_flag
        # print(self.__player_flag)

    # 下子方法
    def make_a_move(self, x, y):
        # 自杀标志位置0
        self.__suicide_flag = 0
        # 全局同形再现标志位置0
        self.__repeat_flag == 0
        # 若鼠标在指定区域内点击
        if x >= 75 and x <= 525 and y >= 75 and y <= 525:
            # 将鼠标事件坐标换算成棋盘行列坐标
            row = (y - 75) // 50
            col = (x - 75) // 50
            if self.__checkerboard_data[row][col] == 0:
                # 将当前棋局压栈
                self.__push()
                # 将下子情况记录在棋盘二维列表中,黑子为-1,白子为1,无子为0
                self.__checkerboard_data[row][col] = self.__player_flag
                # 每下一子即切换玩家
                self.__player_flag = -self.__player_flag
                # print(self.__checkerboard_data)
                # 提去没有“气”的子
                self.__take_out()
                # 如果自杀
                self.__if_suicide(row, col)
                # 如果全局同形再现
                self.__if_repeat()

    # 如果自杀(私有方法)
    def __if_suicide(self, row, col):
        if self.__suicide_flag == 1:
            # print("Suicide is not allowed!")
            # 将自杀的棋子提走
            self.__checkerboard_data[row][col] = 0
            # 玩家切换回自杀者
            self.__player_flag = -self.__player_flag

    # 压栈(私有方法)
    def __push(self):
        self.__stack.append(self.__checkerboard_data)
        if len(self.__stack) > 5:
            self.__stack.pop(0)
        # print(self.__stack)

    # 悔棋方法(待实现)
    def take_back_a_move(self):
        if len(self.__stack) != 0:
            self.__checkerboard_data = self.__stack.pop()

    # 全局同形再现(待实现)
    def __if_repeat(self):
        if self.__repeat_flag == 1:
            pass

    # (*)主游戏方法
    def play(self):
        # 绘制棋盘
        self.__draw_checker()
        # 游戏是否结束
        self.__if_game_over()
        # 打印文本
        self.__print_texts()
        # 绘制棋子
        self.__draw_chesses()
        # 棋子跟随鼠标移动
        self.__chess_follow()

    # 打印文本(私有方法)
    def __print_texts(self):
        # 禁着点提示
        if self.__suicide_flag == 1:
            print_text(font1, 165, 535, "（禁止自杀）", text_color)
        # 全局同形再现提示(待实现)
        # elif self.__repeat_flag == 1:
        #    print_text(font2, 220, 535, "Repeat is not allowed.", text_color)

    # 绘制棋子(私有方法)
    def __draw_chesses(self):
        # 遍历棋盘二维数组,绘制出棋盘中所有已下子
        for i in range(9):
            for j in range(9):
                if self.__checkerboard_data[i][j] == 0:
                    continue
                elif self.__checkerboard_data[i][j] == -1:
                    color = black
                elif self.__checkerboard_data[i][j] == 1:
                    color = white
                pos = j * 50 + 100, i * 50 + 100
                # 棋子填充
                pygame.draw.circle(screen, color, pos, 19, 0)
                # 棋子边框
                pygame.draw.circle(screen, circle_color, pos, 20, 2)

    # 重启游戏方法
    def restart_game(self):
        self.__game_over = 1

    # 清空棋盘(私有方法)
    def __clear_checkerboard(self):
        self.__checkerboard_data = [[0 for i in range(9)] for j in range(9)]

    # 如果游戏结束(私有方法)
    def __if_game_over(self):
        if self.__game_over == 1:
            self.__clear_checkerboard()
            self.__game_over = 0
            self.__player_flag = -1
            self.__stack = []

    # --------------------以下为搜索方法----------------------
    # 深度优先搜索(私有方法)
    # 对于单颗棋子有无“气”的判断,可看做从该点开始作为迷宫的起点,与己方棋子看作迷宫的“通路”,将对方棋子和棋盘边框看作迷宫的“障碍”,将棋盘中的任何空位置看作迷宫的“出口”,只要搜索到任何“出口”,该棋子即有“气”,搜索不到任何“出口”,该棋子无“气”
    # 由于只关心棋子有无“气”,即只需知道能否逃出“迷宫”,而不关心“迷宫”的全部路径或者最短路径等问题,故使用深度优先搜索算法能尽可能快的找到“出口”,从而判断棋子有无“气”
    def __DFS(self, x, y):
        # 为避免重复搜索,走过的位置记为1
        self.__visit[x][y] = 1
        directions = [[x - 1, y], [x + 1, y], [x, y - 1], [x, y + 1]]
        # 左,右,上,下四个方向
        for dx, dy in directions:
            # 左边是墙 或 右边是墙 或 上边是墙 或 下边是墙,即死路,则跳过此方向
            if dx < 0 or dx > 8 or dy < 0 or dy > 8:
                continue
            # 若此方向没有搜索过,则开始搜索
            elif self.__visit[dx][dy] == 0:
                # 此方向没有棋子,可看做迷宫的出口,于是该棋子有“气”,停止搜索
                if self.__checkerboard_data[dx][dy] == 0:
                    self.__isalive_flag = 1
                    return
                # 此方向是对方棋子,是死路,跳过此方向
                elif self.__checkerboard_data[dx][dy] == - self.__checkerboard_data[x][y]:
                    continue
                # 此方向是己方棋子,即通路,继续递归执行DFS
                elif self.__checkerboard_data[dx][dy] == self.__checkerboard_data[x][y]:
                    self.__DFS(dx, dy)
        # 以上条件都不满足,即所有路径都为死路,该棋子无“气”,停止搜索
        return

    # 清空搜索记录(私有方法)
    def __clear_visit(self):
        self.__visit = [[0 for i in range(9)] for j in range(9)]
        self.__isalive_flag = 0

    # 是否有"气"(私有方法)
    def __is_alive(self, x, y):
        isalive = 1  # 用于返回
        # 清空搜索记录
        self.__clear_visit()
        # 执行深度优先搜索
        self.__DFS(x, y)
        # 有“气”标志为0,则返回0,否则为1
        if self.__isalive_flag == 0:
            isalive = 0
        # 清空搜索记录
        self.__clear_visit()
        return isalive

    # 提掉没有“气”的子(私有方法)
    def __take_out(self):
        token_list = []  # “死亡”名单
        # 遍历整个棋盘
        for i in range(9):
            for j in range(9):
                # 若当前位置是空,则直接跳过
                if self.__checkerboard_data[i][j] == 0:
                    continue
                # 判断该棋子有无“气”(只判断对方棋子)
                elif self.__checkerboard_data[i][j] == self.__player_flag and self.__is_alive(i, j) == 0:
                    # 将无“气”的棋子加入“死亡”名单
                    token_list.append([i, j])

        # 若名单不为空,则提去名单中的所有棋子(仅对方棋子)
        if len(token_list) != 0:
            for i, j in token_list:
                self.__checkerboard_data[i][j] = 0

        # 自杀判定
        # 对方无“气”棋子全部提走后,对己方棋子进行有无“气”的判断,若己方仍存在无“气”棋子,则判定为自杀行为,自杀标志置1(因只需检测到一个无“气”子即说明是自杀,故无需继续检测,跳出循环)
        for i in range(9):
            for j in range(9):
                if self.__checkerboard_data[i][j] == - self.__player_flag:
                    if self.__is_alive(i, j) == 0:
                        self.__suicide_flag = 1
                        break


# 实例化Go类
go = Go()

# pygame主循环
while True:
    for event in pygame.event.get():
        # 检测退出
        if event.type == QUIT:
            sys.exit()
        # 检测鼠标事件
        elif event.type == MOUSEMOTION:
            mouse_x, mouse_y = event.pos
            # 获得鼠标当前位置
            go.get_mouse_current_position(mouse_x, mouse_y)
        elif event.type == MOUSEBUTTONUP:
            # 当鼠标左键弹起时,下子
            mouse_up = event.button
            mouse_up_x, mouse_up_y = event.pos
            go.make_a_move(mouse_up_x, mouse_up_y)  # Go类的下子方法
        # 检测键盘事件
        elif event.type == KEYUP:
            # 按回车重启游戏
            if event.key in (K_RETURN, K_r):
                go.restart_game()  # Go类的重启游戏方法
            elif event.key == K_ESCAPE:
                # esc键退出
                sys.exit()
            elif event.key == K_BACKSPACE:
                # 退格键悔棋
                go.take_back_a_move()
            elif event.key == K_s:
                # s键切换玩家
                go.switch_player()

    # 填充背景色
    screen.fill(background_color)
    # 文字
    print_text(font2, 5, 5, "This is a go demo.", (0, 0, 70))
    # Go类的主游戏方法
    go.play()
    # pygame更新
    pygame.display.update()
