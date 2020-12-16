#include "stdio.h"
#include <mongoc.h>

int main() {
    FILE *file = fopen("subscriber.json", "r");

    const char *uri_string = "mongodb://localhost/open5gs";
    mongoc_uri_t *uri;
    mongoc_client_t *db_client;
    mongoc_database_t *database;
    mongoc_collection_t *collection;
    bson_t *command, reply, *insert;
    bson_error_t error;
    char *str;
    bool retval;
    bson_t *doc = NULL;


    mongoc_init ();
    uri = mongoc_uri_new_with_error (uri_string, &error);
    db_client = mongoc_client_new_from_uri (uri);

    char *db_name = (char *)mongoc_uri_get_database(uri);


    collection = mongoc_client_get_collection(
                    db_client,
                    db_name, "subscribers");
    //ABTS_PTR_NOTNULL(tc, collection);

    char json[3200];
    int num_of_subscriber, i;

    fscanf(file,"%d\n",&num_of_subscriber);
    for ( i=0 ; i < num_of_subscriber; ++i ) {
            fgets(json, 3200 ,file);
            /********** Insert Subscriber in Database */
            doc = bson_new_from_json((const uint8_t *)json, -1, &error);
            printf("INSERT Subscriber\n");
            printf("%s\n",json);
            //ABTS_PTR_NOTNULL(tc, doc);

            int insert_res = mongoc_collection_insert(collection, MONGOC_INSERT_NONE, doc, NULL, &error);
            //ABTS_TRUE(tc, insert_res);
            if(!insert_res) {
                    fprintf (stderr, "ERROR: %d.%d: %s\n", error.domain, error.code, error.message);
                    return 0;
            }
            bson_destroy(doc);
    }


    fclose(file);

    return 0;
}
