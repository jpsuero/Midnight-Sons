#include "Highscore.h"
#include "simple_json.h"
#include "simple_logger.h"

int highscore_load(char* filename)
{
	SJson* json;
	int highscore = 0;

	json = sj_load(filename);
	sj_get_integer_value(sj_object_get_value(json, "highscore"), &highscore);
	slog("%i", highscore);

	return highscore;
	

}

void highscore_save(int score)
{
	SJson* json;

	json = sj_object_new();

	sj_object_insert(json, "highscore", sj_new_int(score));

	sj_save(json, "levels/testlevel.json");
}