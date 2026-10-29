#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "knowledge.h"
#include "experiment.h"
#include "game.h"
#include "profile.h"
#include "utils.h"

int main() {
    // 初始化知识库
    init_knowledge_base();

    // 用户登录/注册
    printf("=== ? 欢迎来到AI探索乐园! ===\n");
    printf("请输入你的名字: ");
    char username[MAX_USERNAME];
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';
    trim(username);

    UserProfile profile;
    if(!load_profile(&profile, username)) {
        printf("新朋友！为你创建学习档案。\n");
        init_profile(username);
    } else {
        printf("欢迎回来，%s!\n", username);
    }

    int choice;
    do {
        printf("\n========== 主菜单 ==========\n");
        printf("1. AI知识百科(问答学习)\n");
        printf("2. AI原理小实验\n");
        printf("3. AI幻觉检测游戏\n");
        printf("4. 我的学习档案\n");
        printf("5. 保存并退出\n");
        printf("请选择: ");
        scanf("%d", &choice);
        CLEAR_BUFFER();

        switch(choice) {
            case 1:
                {
                    int sub;
                    do {
                        printf("\n--- 知识百科 ---\n");
                        printf("1. 按主题浏览\n");
                        printf("2. 关键词搜索\n");
                        printf("3. 有边界问答(只给提示)\n");
                        printf("0. 返回主菜单\n");
                        printf("请选择: ");
                        scanf("%d", &sub);
                        CLEAR_BUFFER();
                        switch(sub) {
                            case 1: browse_by_topic(); break;
                            case 2: search_by_keyword(); break;
                            case 3: ask_with_hint(); break;
                            case 0: break;
                            default: printf("无效选项。\n");
                        }
                    } while(sub != 0);
                }
                break;
            case 2:
                {
                    int sub;
                    do {
                        printf("\n--- AI原理小实验 ---\n");
                        printf("1. 动物分类决策树\n");
                        printf("2. 水果分类器（简单机器学习）\n");
                        printf("0. 返回主菜单\n");
                        printf("请选择: ");
                        scanf("%d", &sub);
                        CLEAR_BUFFER();
                        switch(sub) {
                            case 1:
                                animal_classifier();
                                complete_experiment(&profile, "animal_classifier");
                                break;
                            case 2:
                                fruit_classifier();
                                complete_experiment(&profile, "fruit_classifier");
                                break;
                            case 0: break;
                            default: printf("无效选项。\n");
                        }
                    } while(sub != 0);
                }
                break;
            case 3:   // AI科普挑战赛
                {
                int score = quiz_game();           // 获取游戏得分
                // 更新学习档案：总分增加得分，实验次数+1
                profile.total_points += score;
                profile.experiments_done++;
                // 可选：立即保存档案，防止退出前丢失
                save_profile(&profile);
                printf("本次游戏得分已计入学习档案！\n");
                 }
                break;
            case 4:
                show_progress(&profile);
                break;
            case 5:
                if(save_profile(&profile)) {
                    printf("档案保存成功！再见，%s!\n", profile.username);
                } else {
                    printf("保存失败，请检查磁盘空间。\n");
                }
                break;
            default:
                printf("无效选项，请重新输入。\n");
        }
    } while(choice != 5);

    return 0;
}