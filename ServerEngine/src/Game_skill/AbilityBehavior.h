//技能流程 前摇过程-结算点-后摇过程

#ifndef TL_ABILITY_BEHAVIOR_H
#define TL_ABILITY_BEHAVIOR_H

enum {
    DOTA_ABILITY_BEHAVIOR_HIDDEN               = 1 << 0, //这个技能是单位所拥有的技能，但是不会在HUD上显示。
    DOTA_ABILITY_BEHAVIOR_PASSIVE              = 1 << 1, //这个技能是一个被动技能，不能被使用，但是会在HUD上显示。
    DOTA_ABILITY_BEHAVIOR_NO_TARGET            = 1 << 2, //不需要指定目标就能释放的技能，当按下技能按钮的时候，这个技能就会被释放。
    DOTA_ABILITY_BEHAVIOR_UNIT_TARGET          = 1 << 3, //技能需要指定一个目标来释放。
    DOTA_ABILITY_BEHAVIOR_POINT                = 1 << 4, //技能将会在鼠标指定的位置释放（如果鼠标指向了一个单位，会在单位所在的位置释放）。
    DOTA_ABILITY_BEHAVIOR_AOE                  = 1 << 5, //这个技能将会显示技能释放的范围，有点像DOTA_ABILITY_BEHAVIOR_POINT类的技能，但是会显示一个范围。
    DOTA_ABILITY_BEHAVIOR_NOT_LEARNABLE        = 1 << 6, //这个技能将能被释放，或者拥有对应的释放机制，但是不能被学习。（一般是用在类似炸弹人的引爆炸弹技能）。
    DOTA_ABILITY_BEHAVIOR_CHANNELLED           = 1 << 7, //持续性施法技能，如果施法者移动或者被沉默，这个技能将会被中断。
    DOTA_ABILITY_BEHAVIOR_ITEM                 = 1 << 8, //这个技能绑定了一个物品。
    DOTA_ABILITY_BEHAVIOR_TOGGLE               = 1 << 9, //切换类技能。
    DOTA_ABILITY_BEHAVIOR_DIRECTIONAL          = 1 << 10, //这个技能是一个从英雄出发的方向性技能，比如米拉娜的月之神剑或者屠夫的肉钩。
    DOTA_ABILITY_BEHAVIOR_IMMEDIATE            = 1 << 11, //这个技能将会被立即释放，不会进入操作序列。
    DOTA_ABILITY_BEHAVIOR_AUTOCAST             = 1 << 12, //这个技能可以被自动释放。
    DOTA_ABILITY_BEHAVIOR_NOASSIST             = 1 << 13, //这个技能将不会有辅助网格。
    DOTA_ABILITY_BEHAVIOR_AURA                 = 1 << 14, //这个技能是一个光环技能，Not really used other than to tag the ability as such.
    DOTA_ABILITY_BEHAVIOR_ATTACK               = 1 << 15, //这个技能是一个法球技能，不能对魔法免疫目标生效，
    DOTA_ABILITY_BEHAVIOR_DONT_RESUME_MOVEMENT = 1 << 16, //这个技能在释放完成之后不会继续之前的移动操作，只能和无目标或者立即释放类技能配合使用。
    DOTA_ABILITY_BEHAVIOR_ROOT_DISABLES        = 1 << 17, //这个技能在单位被定身的时候无法使用。
    DOTA_ABILITY_BEHAVIOR_UNRESTRICTED         = 1 << 18, //这个技能在释放指令被限制的时候也能被使用。
    DOTA_ABILITY_BEHAVIOR_IGNORE_PSEUDO_QUEUE  = 1 << 19, //这个技能在被眩晕，施法和被强制攻击的时候也能使用，只能和自动释放类DOTA_ABILITY_BEHAVIOR_AUTOCAST配合使用。
    DOTA_ABILITY_BEHAVIOR_IGNORE_CHANNEL       = 1 << 20, //这个技能即使施法被中断也能继续释放。
    DOTA_ABILITY_BEHAVIOR_DONT_CANCEL_MOVEMENT = 1 << 21, //Doesn't cause certain modifiers to end, 目前未知，只在信使的速度爆发有见到。
    DOTA_ABILITY_BEHAVIOR_DONT_ALERT_TARGET    = 1 << 22, //这个技能在指定敌人释放的时候将不会惊醒他们。
    DOTA_ABILITY_BEHAVIOR_DONT_RESUME_ATTACK   = 1 << 23, //这个技能在释放完成之后，将不会恢复对之前目标的自动攻击，只能配合无目标，非立即释放类和指定单位目标类技能使用。
    DOTA_ABILITY_BEHAVIOR_NORMAL_WHEN_STOLEN   = 1 << 24, //这个技能在被偷取之后，依然使用之前的施法前摇。
    DOTA_ABILITY_BEHAVIOR_IGNORE_BACKSWING     = 1 << 25, //这个技能将会无视施法后摇。
    DOTA_ABILITY_BEHAVIOR_RUNE_TARGET          = 1 << 26, //这个技能能以神符为目标。
};

class AbilityBehavior
{
private:

};

#endif