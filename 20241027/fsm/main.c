/**
 * @file main.c
 * @brief main
 * @author ruleline (ruleline@outlook.com)
 * @since 2024-10-27
 *
 * @authors ruleline (ruleline@outlook.com)
 * @date 2024-10-27
 * @version 0.00.001
 *
 * @copyright ©2024 UNISAR
 *
 * @details
 * -----------------------------------------------------------------------------
 *    version   |    date    |     author     |             comments
 * ------------ | ---------- | -------------- | --------------------------------
 *   0.00.001   | 2024-10-27 |    ruleline    | 初版
 * -----------------------------------------------------------------------------
 */

#include "fsm.h"

/**
 * @brief 主任务
 *
 * @return 0
 */
int main(void)
{
        fsm_init();

        for (;;) {
                fsm_run();
        }

        fsm_deinit();
        return 0;
}
