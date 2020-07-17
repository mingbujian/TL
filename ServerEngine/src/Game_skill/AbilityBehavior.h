//�������� ǰҡ����-�����-��ҡ����

#ifndef TL_ABILITY_BEHAVIOR_H
#define TL_ABILITY_BEHAVIOR_H

enum {
    DOTA_ABILITY_BEHAVIOR_HIDDEN               = 1 << 0, //��������ǵ�λ��ӵ�еļ��ܣ����ǲ�����HUD����ʾ��
    DOTA_ABILITY_BEHAVIOR_PASSIVE              = 1 << 1, //���������һ���������ܣ����ܱ�ʹ�ã����ǻ���HUD����ʾ��
    DOTA_ABILITY_BEHAVIOR_NO_TARGET            = 1 << 2, //����Ҫָ��Ŀ������ͷŵļ��ܣ������¼��ܰ�ť��ʱ��������ܾͻᱻ�ͷš�
    DOTA_ABILITY_BEHAVIOR_UNIT_TARGET          = 1 << 3, //������Ҫָ��һ��Ŀ�����ͷš�
    DOTA_ABILITY_BEHAVIOR_POINT                = 1 << 4, //���ܽ��������ָ����λ���ͷţ�������ָ����һ����λ�����ڵ�λ���ڵ�λ���ͷţ���
    DOTA_ABILITY_BEHAVIOR_AOE                  = 1 << 5, //������ܽ�����ʾ�����ͷŵķ�Χ���е���DOTA_ABILITY_BEHAVIOR_POINT��ļ��ܣ����ǻ���ʾһ����Χ��
    DOTA_ABILITY_BEHAVIOR_NOT_LEARNABLE        = 1 << 6, //������ܽ��ܱ��ͷţ�����ӵ�ж�Ӧ���ͷŻ��ƣ����ǲ��ܱ�ѧϰ����һ������������ը���˵�����ը�����ܣ���
    DOTA_ABILITY_BEHAVIOR_CHANNELLED           = 1 << 7, //������ʩ�����ܣ����ʩ�����ƶ����߱���Ĭ��������ܽ��ᱻ�жϡ�
    DOTA_ABILITY_BEHAVIOR_ITEM                 = 1 << 8, //������ܰ���һ����Ʒ��
    DOTA_ABILITY_BEHAVIOR_TOGGLE               = 1 << 9, //�л��༼�ܡ�
    DOTA_ABILITY_BEHAVIOR_DIRECTIONAL          = 1 << 10, //���������һ����Ӣ�۳����ķ����Լ��ܣ����������ȵ���֮�񽣻���������⹳��
    DOTA_ABILITY_BEHAVIOR_IMMEDIATE            = 1 << 11, //������ܽ��ᱻ�����ͷţ��������������С�
    DOTA_ABILITY_BEHAVIOR_AUTOCAST             = 1 << 12, //������ܿ��Ա��Զ��ͷš�
    DOTA_ABILITY_BEHAVIOR_NOASSIST             = 1 << 13, //������ܽ������и�������
    DOTA_ABILITY_BEHAVIOR_AURA                 = 1 << 14, //���������һ���⻷���ܣ�Not really used other than to tag the ability as such.
    DOTA_ABILITY_BEHAVIOR_ATTACK               = 1 << 15, //���������һ�������ܣ����ܶ�ħ������Ŀ����Ч��
    DOTA_ABILITY_BEHAVIOR_DONT_RESUME_MOVEMENT = 1 << 16, //����������ͷ����֮�󲻻����֮ǰ���ƶ�������ֻ�ܺ���Ŀ����������ͷ��༼�����ʹ�á�
    DOTA_ABILITY_BEHAVIOR_ROOT_DISABLES        = 1 << 17, //��������ڵ�λ�������ʱ���޷�ʹ�á�
    DOTA_ABILITY_BEHAVIOR_UNRESTRICTED         = 1 << 18, //����������ͷ�ָ����Ƶ�ʱ��Ҳ�ܱ�ʹ�á�
    DOTA_ABILITY_BEHAVIOR_IGNORE_PSEUDO_QUEUE  = 1 << 19, //��������ڱ�ѣ�Σ�ʩ���ͱ�ǿ�ƹ�����ʱ��Ҳ��ʹ�ã�ֻ�ܺ��Զ��ͷ���DOTA_ABILITY_BEHAVIOR_AUTOCAST���ʹ�á�
    DOTA_ABILITY_BEHAVIOR_IGNORE_CHANNEL       = 1 << 20, //������ܼ�ʹʩ�����ж�Ҳ�ܼ����ͷš�
    DOTA_ABILITY_BEHAVIOR_DONT_CANCEL_MOVEMENT = 1 << 21, //Doesn't cause certain modifiers to end, Ŀǰδ֪��ֻ����ʹ���ٶȱ����м�����
    DOTA_ABILITY_BEHAVIOR_DONT_ALERT_TARGET    = 1 << 22, //���������ָ�������ͷŵ�ʱ�򽫲��ᾪ�����ǡ�
    DOTA_ABILITY_BEHAVIOR_DONT_RESUME_ATTACK   = 1 << 23, //����������ͷ����֮�󣬽�����ָ���֮ǰĿ����Զ�������ֻ�������Ŀ�꣬�������ͷ����ָ����λĿ���༼��ʹ�á�
    DOTA_ABILITY_BEHAVIOR_NORMAL_WHEN_STOLEN   = 1 << 24, //��������ڱ�͵ȡ֮����Ȼʹ��֮ǰ��ʩ��ǰҡ��
    DOTA_ABILITY_BEHAVIOR_IGNORE_BACKSWING     = 1 << 25, //������ܽ�������ʩ����ҡ��
    DOTA_ABILITY_BEHAVIOR_RUNE_TARGET          = 1 << 26, //��������������ΪĿ�ꡣ
};

class AbilityBehavior
{
private:

};

#endif