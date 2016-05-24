#ifndef __DEVICEAPI_H__
#define __DEVICEAPI_H__


	void deviceapi_get_gateway (int session,Json::Value &request);
	void deviceapi_get_gateway_about (int session,Json::Value &request);
	void deviceapi_get_accessory_about (int session,Json::Value &request);
	void deviceapi_get_accessory_detail (int session,Json::Value &request);
	void deviceapi_get_group_free_lights (int session,Json::Value &request);
	void deviceapi_set_detail (int session,Json::Value &request);
	void deviceapi_remove (int session,Json::Value &request);
	void deviceapi_get_activities (int session,Json::Value &request);
	void deviceapi_get_light_effects (int session,Json::Value &request);
	void deviceapi_set_light_effects (int session,Json::Value &request);
	void deviceapi_get_gateway (int session,Json::Value &request);
	void deviceapi_add_accessories (int session,Json::Value &request);
	void deviceapi_merge_accessories (int session,Json::Value &request);
	void deviceapi_backup_gateway (int session,Json::Value &request);
	void deviceapi_restore_gateway (int session,Json::Value &request);
	void deviceapi_reset_gateway (int session,Json::Value &request);
	void deviceapi_update_gateway (int session,Json::Value &request);
	void deviceapi_get_detail (int session,Json::Value &request);
	void deviceapi_get_other_groups (int session,Json::Value &request);
	//void deviceapi_set_detail (int session,Json::Value &request);
	void deviceapi_add_an_accessory_to_group (int session,Json::Value &request);
	//void deviceapi_remove_accessories_from_group (int session,Json::Value &request);
	void deviceapi_get_locations (int session,Json::Value &request);
	void deviceapi_add_accessories_to_location (int session,Json::Value &request);
	void deviceapi_create_a_location (int session,Json::Value &request);
	void deviceapi_remove_locations (int session,Json::Value &request);
	//void deviceapi_get_detail (int session,Json::Value &request);
	void deviceapi_set_schedule_detail (int session,Json::Value &request);
	void deviceapi_add_a_schedule (int session,Json::Value &request);
	//void deviceapi_remove_a_schedule (int session,Json::Value &request);
	void deviceapi_get_accessory_setting (int session,Json::Value &request);
	void deviceapi_get_gateway_setting (int session,Json::Value &request);
	void deviceapi_set_accessory_setting (int session,Json::Value &request);
	//void deviceapi_set_accessory_setting (int session,Json::Value &request);
	void deviceapi_set_gateway_setting (int session,Json::Value &request);
	void deviceapi_get_objects (int session,Json::Value &request);
	//void deviceapi_get_detail (int session,Json::Value &request);
	//void deviceapi_set_detail (int session,Json::Value &request);
	void deviceapi_remove_a_switch_accessory (int session,Json::Value &request);
	void deviceapi_get_tasks (int session,Json::Value &request);
	//void deviceapi_get_detail (int session,Json::Value &request);
	//void deviceapi_set_detail(session,value);
	void deviceapi_add_a_task (int session,Json::Value &request);
	//void deviceapi_remove (int session,Json::Value &request);

#endif