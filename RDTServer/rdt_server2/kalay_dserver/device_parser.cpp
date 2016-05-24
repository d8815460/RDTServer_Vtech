#include "../headers/unixclientstream.hpp"
#include "../headers/exception.hpp"
#include <string>
#include <iostream>
#include <string.h>
#include <unistd.h>

#include <iomanip> 
#include <json/json.h>


#include "kalay_dserver.h"
#include "dserver.h"
#include "device_parser.h"
#include "device_api.h"

using namespace std;


int device_parser(int session,unsigned char *option,int option_len,unsigned char *data,int data_len)
{
	Json::Reader reader;
	Json::Value value;
	


	if (reader.parse((char*) data, value))
	{
		string uid = value["uid"].asString();
		string api = value["api"].asString();


		if ( option != NULL && (option[1]&0x01) )
		{

			unsigned int rdt_ticket_no;

			rdt_ticket_no = (((unsigned int)option[2]) << 8 ) | option[3] ;

			value["rdt_ticket"] = rdt_ticket_no;
		}


		printf("UID:%s\n",uid.c_str());
		printf("api:%s\n",api.c_str());

		if ( strcmp(api.c_str(),"get_gateway_about") == 0 ) //
		{
			deviceapi_get_gateway_about(session,value);
		}
		else if ( strcmp(api.c_str(),"get_accessory_about") == 0 ) //
		{
			deviceapi_get_accessory_about(session,value);
		}
		else if ( strcmp(api.c_str(),"get_accessory_detail") == 0 ) //
		{
			deviceapi_get_accessory_detail(session,value);
		}
		else if ( strcmp(api.c_str(),"get_group_free_lights") == 0 ) //
		{
			deviceapi_get_group_free_lights(session,value);
		}
		else if ( strcmp(api.c_str(),"set_detail") == 0 ) //
		{
			deviceapi_set_detail(session,value);
		}
		else if ( strcmp(api.c_str(),"remove") == 0 ) //
		{
			deviceapi_remove(session,value);
		}
		else if ( strcmp(api.c_str(),"get_activities") == 0 ) //
		{
			deviceapi_get_activities(session,value);
		}
		else if ( strcmp(api.c_str(),"get_light_effects") == 0 ) //
		{
			deviceapi_get_light_effects(session,value);
		}
		else if ( strcmp(api.c_str(),"set_light_effects") == 0 ) //
		{
			deviceapi_set_light_effects(session,value);
		}
		else if ( strcmp(api.c_str(),"get_gateway") == 0 ) //
		{
			deviceapi_get_gateway(session,value);
		}
		else if ( strcmp(api.c_str(),"add_accessories") == 0 ) //
		{
			deviceapi_add_accessories(session,value);
		}
		else if ( strcmp(api.c_str(),"merge_accessories") == 0 ) //
		{
			deviceapi_merge_accessories(session,value);
		}
		else if ( strcmp(api.c_str(),"backup_gateway") == 0 ) //
		{
			deviceapi_backup_gateway(session,value);
		}
		else if ( strcmp(api.c_str(),"restore_gateway") == 0 ) //
		{
			deviceapi_restore_gateway(session,value);
		}
		else if ( strcmp(api.c_str(),"reset_gateway") == 0 ) //
		{
			deviceapi_reset_gateway(session,value);
		}
		else if ( strcmp(api.c_str(),"update_gateway") == 0 ) //
		{
			deviceapi_update_gateway(session,value);
		}
		else if ( strcmp(api.c_str(),"get_detail") == 0 ) //
		{
			deviceapi_get_detail(session,value);
		}
		else if ( strcmp(api.c_str(),"get_other_groups") == 0 ) //
		{
			deviceapi_get_other_groups(session,value);
		}
//		else if ( strcmp(api.c_str(),"set_detail") == 0 ) //
//		{
//			deviceapi_set_detail(session,value);
//		}
		else if ( strcmp(api.c_str(),"add_an_accessory_to_group") == 0 ) //
		{
			deviceapi_add_an_accessory_to_group(session,value);
		}
//		else if ( strcmp(api.c_str(),"remove_accessories_from_group") == 0 ) //
//		{
//			deviceapi_remove_accessories_from_group(session,value);
//		}
		else if ( strcmp(api.c_str(),"get_locations") == 0 ) //
		{
			deviceapi_get_locations(session,value);
		}
		else if ( strcmp(api.c_str(),"add_accessories_to_location") == 0 ) //
		{
			deviceapi_add_accessories_to_location(session,value);
		}
		else if ( strcmp(api.c_str(),"create_a_location") == 0 ) //
		{
			deviceapi_create_a_location(session,value);
		}
//		else if ( strcmp(api.c_str(),"remove_locations") == 0 ) //
//		{
//			deviceapi_remove_locations(session,value);
//		}
//		else if ( strcmp(api.c_str(),"get_detail") == 0 ) //
//		{
//			deviceapi_get_detail(session,value);
//		}
		else if ( strcmp(api.c_str(),"set_schedule_detail") == 0 ) //
		{
			deviceapi_set_schedule_detail(session,value);
		}
		else if ( strcmp(api.c_str(),"add_a_schedule") == 0 ) //
		{
			deviceapi_add_a_schedule(session,value);
		}
//		else if ( strcmp(api.c_str(),"remove_a_schedule") == 0 ) //
//		{
//			deviceapi_remove_a_schedule(session,value);
//		}
		else if ( strcmp(api.c_str(),"get_accessory_setting") == 0 ) //
		{
			deviceapi_get_accessory_setting(session,value);
		}
		else if ( strcmp(api.c_str(),"get_gateway_setting") == 0 ) //
		{
			deviceapi_get_gateway_setting(session,value);
		}
		else if ( strcmp(api.c_str(),"set_accessory_setting") == 0 ) //
		{
			deviceapi_set_accessory_setting(session,value);
		}
//		else if ( strcmp(api.c_str(),"set_accessory_setting") == 0 ) //
//		{
//			deviceapi_set_accessory_setting(session,value);
//		}
		else if ( strcmp(api.c_str(),"set_gateway_setting") == 0 ) //
		{
			deviceapi_set_gateway_setting(session,value);
		}
		else if ( strcmp(api.c_str(),"get_objects") == 0 ) //
		{
			deviceapi_get_objects(session,value);
		}
//		else if ( strcmp(api.c_str(),"get_detail") == 0 ) //
//		{
//			deviceapi_get_detail(session,value);
//		}
//		else if ( strcmp(api.c_str(),"set_detail") == 0 ) //
//		{
//			deviceapi_set_detail(session,value);
//		}
//		else if ( strcmp(api.c_str(),"remove_a_switch_accessory") == 0 ) //
//		{
//			deviceapi_remove_a_switch_accessory(session,value);
//		}		
		else if ( strcmp(api.c_str(),"get_tasks") == 0 ) //
		{
			deviceapi_get_tasks(session,value);
		}
//		else if ( strcmp(api.c_str(),"get_detail") == 0 ) //
//		{
//			deviceapi_get_detail(session,value);
//		}
//		else if ( strcmp(api.c_str(),"set_detail") == 0 ) //
//		{
//			deviceapi_set_detail(session,value);
//		}
		else if ( strcmp(api.c_str(),"add_a_task") == 0 ) //
		{
			deviceapi_add_a_task(session,value);
		}
//		else if ( strcmp(api.c_str(),"remove") == 0 ) //
//		{
//			deviceapi_remove(session,value);
//		}

	}
	else
	{
		printf("Receive a non-json format string\n");
	}

	return 0;

}
