#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/**
 * 中国上海头脑奥林匹克协会
 * 编程1小时 嘉年华·青少年科技创新大赛
 *
 * 袁腾霄 
 * 马桥文来外国语小学 三（7）班
 * 指导老师：刘老师，王老师
 * 
 * 本次作品：命令行下的扫雷游戏
 */

// 定义雷区大小
int H = 7;
int W = 7;

// 统计一共踩过多少个格子
int numOfVisisted(int visited[H][W]) {
    int c = 0;
    for (int i = 1; i < H; i++) {
        for (int j = 1; j < W; j++) {
            if (visited[i][j] >= 0) {
                c++;                //踩过的个数
            }
        }
    }
    return c;
}

// 显示雷区，
// 当前位置：空格
// 标记过的位置：X
// 踩过的位置：四周雷的个数
// 其他：#
void printMatrix(int visited[H][W], int x, int y) {
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            if (i == x && j == y) {
                printf(" ");
            } else if (visited[i][j] == -1) {
                printf("#");
            } else if (visited[i][j] == -2) {
                printf("X");
            } 
            else {
                printf("%d", visited[i][j]);
            }
        }
        printf("\n");
    }
}
int main () {
    //输出游戏操作须知
    printf("\n\t按'w' 'a' 's' 'd'进行前后左右移动\n\t按空格挖雷\n\t按'y'进行标记\n\t按任何键继续\n");
    // 控制回显
    system("stty -icanon");
    system("stty -echo");
    getchar();
    //初始化随机函数
    srand(time (0));
    //储存炸弹的位置
    int bomb[H][W];  
    int bombcount = 0;
    // 初始化bomb数组，10%概率为炸弹，边界不会有炸弹               
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            bomb[i][j] = 0;
            int suijishu = rand() % 100;//0-99
            if (suijishu < 10) {
                if (i != 0 & i != H - 1 && j != 0 && j != W - 1) {
                    bomb[i][j] = 1;
                    bombcount++;
                }
            }
        }
    }
    // 存储被踩过的地方 
    //  -1: 没踩过， 
    //  -2：标记 
    //  其他：踩过，并为四周炸弹个数
    int visited[H][W];
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            visited[i][j] = -1;
        }
    }
    // x、y为当前位置
    int x = 1;
    int y = 1;
    //定义定义ch为用户按键
    char ch = 'h';
    // 按下q就立即退出
    while (ch != 'q') {
        // 'w' 'a' 's' 'd'分别控制前后左右
        // 同时控制不允许走到边界
        if (ch == 'w' && x > 1) {
            x--;
        }else if (ch == 'a' && y > 1) {
            y--;
        } else if (ch == 's' && x < H - 2) {
            x++;
        } else if (ch == 'd' && y < W - 2) {
            y++;
        } else if (ch == 'y') {
            // 标记当前位置
            visited[x][y] = -2;
        } else if (ch == ' ') {
             // 踩当前位置
            if (bomb[x][y] == 1) {
                printf("你踩到炸弹了！！！！！\n");
                break;
            } else {
                // 当前位置不是炸弹，统计四周炸弹个数
                // 并存入到visited数组
                int numBomb = 0;
                for (int ii = x - 1; ii <= x + 1; ii++) {
                    for (int jj = y - 1; jj <= y + 1; jj++) {
                        numBomb += bomb[ii][jj];
                    }
                }
                // 判断是否踩完所有的非雷区，并且退出
                visited[x][y] = numBomb;
                int c = numOfVisisted(visited);
                if (bombcount + c == (H - 2) * (W - 2)) {
                    printf("你胜利了！！！\n");
                    break;
                }
            }
        }
        //清屏
        system("clear");
        //显示整个盘面
        printMatrix(visited, x, y);
        ch = getchar();
    }
    return 0;
}