int is_wanted(object me)
{
	if (me->query_condition("killer")) {
		notify_fail("�㻹���˽��꽭����Թ��˵�ɡ�\n");
		return 1;
	}
	if (sizeof(filter_array(deep_inventory(me), (: userp :)))) {
		notify_fail("���뷷���˿ڰ���\n");
		return 1;
	}
	return 0;
}