#include <stdio.h>
#include <sqlite3.h> 

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   for(i = 0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   
   printf("\n");
   return 0;
}

int main(int argc, char* argv[]) {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data = "Callback function called";

   rc = sqlite3_open("DB.SQLite", &db);

   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */
//   sql = "SELECT name FROM sqlite_schema WHERE type='table' AND name NOT LIKE 'sqlite_%'";
//   sql = "SELECT * FROM nova_widget LIMIT 1";
//   sql = "SELECT * FROM nova_playlist LIMIT 1";

/*
// выборка всех роликов
   sql = "SELECT nova_playlist.name, nova_page.viewOrder, nova_widget.name, nova_widget.duration FROM nova_playlist \
		LEFT JOIN nova_relation_playlist2scene ON nova_playlist.uuid = nova_relation_playlist2scene.playlistuuid \
		LEFT JOIN nova_relation_scene2page ON nova_relation_playlist2scene.sceneuuid = nova_relation_scene2page.sceneuuid \
		LEFT JOIN nova_page ON nova_relation_scene2page.pageuuid = nova_page.uuid \
		LEFT JOIN nova_relation_page2widget ON nova_relation_scene2page.pageuuid = nova_relation_page2widget.pageuuid \
		LEFT JOIN nova_widget ON nova_relation_page2widget.widgetuuid = nova_widget.uuid \
		ORDER BY nova_playlist.name, nova_page.viewOrder";
*/

// выборка роликов, кроме идущих в пн,ср,пт
   sql = "SELECT nova_playlist.name, nova_page.viewOrder, nova_widget.name, nova_widget.duration FROM nova_playlist \
		LEFT JOIN nova_relation_playlist2scene ON nova_playlist.uuid = nova_relation_playlist2scene.playlistuuid \
		LEFT JOIN nova_scene ON nova_relation_playlist2scene.sceneuuid = nova_scene.uuid \
		LEFT JOIN nova_relation_scene2page ON nova_relation_playlist2scene.sceneuuid = nova_relation_scene2page.sceneuuid \
		LEFT JOIN nova_page ON nova_relation_scene2page.pageuuid = nova_page.uuid \
		LEFT JOIN nova_relation_page2widget ON nova_relation_scene2page.pageuuid = nova_relation_page2widget.pageuuid \
		LEFT JOIN nova_widget ON nova_relation_page2widget.widgetuuid = nova_widget.uuid \
		WHERE nova_scene.constraints NOT LIKE '%2,4,6%' \
		ORDER BY nova_playlist.name, nova_page.viewOrder";


   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Operation done successfully\n");
   }

   sqlite3_close(db);
}
