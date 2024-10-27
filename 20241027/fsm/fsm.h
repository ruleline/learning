/**
 * @file fsm.h
 * @brief fsm
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

#if !defined FSM_H
#define FSM_H

/**
 * @brief fsm初始化
 *
 */
void fsm_init(void);

/**
 * @brief fsm反初始化
 *
 */
void fsm_deinit(void);

/**
 * @brief fsm运行
 *
 */
void fsm_run(void);

#endif /* !defined FSM_H */
