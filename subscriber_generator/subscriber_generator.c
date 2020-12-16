#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
 * Writing subsriber infos into file with jason format
 * */
int create_subscriber(int num_of_subscriber) {
    FILE *file = fopen("subscriber.json", "w");
    int i;

    if ( file == NULL ) {
	    fprintf(stderr, "File open error\n");
	    return 0;
    }

    fprintf(file,"%d\n",num_of_subscriber);

    for ( i=0 ; i<num_of_subscriber ; ++i ) {
            int ue_id = i; // 
            char json1[] =   "{"
                    "\"_id\" : { \"$oid\" : \"";
            char oid_1[] = "597223158b8861d7605378c6";
	    char temp_char[2];
	    int temp_id;
	    int loop_index;
	    temp_id = 0x605378c6 + ue_id;
	    loop_index = strlen(oid_1)-1;
	    while(temp_id != 0 ) {
	    	sprintf(temp_char, "%x", temp_id%16);
		oid_1[loop_index] = temp_char[0];
		loop_index--;
		temp_id /= 16;
	    }

            char json2[] =
                    "\" }, "
                    "\"imsi\" : \"";
            //char imsi[] = "001010123456819" ;
	    char imsi[] = "901700000021309" ;
            loop_index = strlen(imsi)-1;
            temp_id = ue_id + 21309; // 90170000021309
            while(temp_id != 0) {
		    sprintf(temp_char, "%d", temp_id%10);
		    imsi[loop_index] = temp_char[0];
		    loop_index--;
                    temp_id /= 10;
            }
            char json3[] = "\", "
                    "\"pdn\" : ["
                    "{"
                    "\"apn\" : \"internet\", "
                    "\"_id\" : { \"$oid\" : \"";
            char oid_2[] = "597223158b8861d7605378c7";
	    temp_id = 0x605378c7 + ue_id;
	    loop_index = strlen(oid_2)-1;
	    while( temp_id != 0 ) {
	    	sprintf(temp_char,"%x",temp_id%16);
		oid_2[loop_index] = temp_char[0];
		loop_index--;
		temp_id /= 16;
	    }
            char json4[] = "\" }, "
                    "\"ambr\" : {"
                    "\"uplink\" : { \"$numberLong\" : \"1024000\" }, "
                    "\"downlink\" : { \"$numberLong\" : \"1024000\" } "
                    "},"
                    "\"qos\" : { "
                    "\"qci\" : 9, "
                    "\"arp\" : { "
                    "\"priority_level\" : 8,"
                    "\"pre_emption_vulnerability\" : 1, "
                    "\"pre_emption_capability\" : 1"
                    "} "
                    "}, "
                    "\"type\" : 2"
                    "}"
                    "],"
                    "\"ambr\" : { "
                    "\"uplink\" : { \"$numberLong\" : \"1024000\" }, "
                    "\"downlink\" : { \"$numberLong\" : \"1024000\" } "
                    "},"
                    "\"subscribed_rau_tau_timer\" : 12,"
                    "\"network_access_mode\" : 2, "
                    "\"subscriber_status\" : 0, "
                    "\"access_restriction_data\" : 32, "
                    "\"security\" : { ";
            char k_str[] = "\"k\" : \"465B5CE8 B199B49F AA5F0A2E E238A6BC\", ";
            char opc_str[] = "\"opc\" : \"E8ED289D EBA952E4 283B54E8 8E6183CA\", ";
            char amf_str[] = "\"amf\" : \"8000\", ";
            char sqn_str[] = "\"sqn\" : { \"$numberLong\" : \"64\" }, ";
            char rand_str[] = "\"rand\" : \"20080C38 18183B52 2614162C 07601D0D\" ";
            char json5[] =
                    "}, "
                    "\"__v\" : 0 "
                    "}";
            char *json;
            json = malloc( (1 + strlen(json1) + +strlen(oid_1) +
                                    strlen(imsi) + strlen(json2) + strlen(json3) + strlen(oid_2) + strlen(json4) +
                                    strlen(k_str) + strlen(opc_str) + strlen(amf_str) + strlen(sqn_str) + strlen(rand_str) +
                                    strlen(json5)) *sizeof(char));
            strcpy(json,json1);
            strcat(json,oid_1);
            strcat(json,json2);
            strcat(json,imsi);
            strcat(json,json3);
            strcat(json,oid_2);
            strcat(json,json4);
            strcat(json,k_str);
            strcat(json,opc_str);
            strcat(json,amf_str);
            strcat(json,sqn_str);
            strcat(json,rand_str);
            strcat(json,json5);

            fprintf(file,"%s\n",json);

            free(json);
    }

    fclose(file);
    return 1;
}

int main(int argc, char *argv[]) {

	if ( argc > 1 ) {
		int num = 0 ;
		int i = 0 ;
		for ( i = 0 ; argv[1][i] ; ++i )
			num = num*10 + argv[1][i]-'0';
		if ( num > 0 )
		if ( create_subscriber(num) ) {
			printf("Done\n");
			return 0;
		}
		fprintf(stderr, "number of subscriber miss/error\n");
	}
	printf("ERROR\n");
	return 0;
}
