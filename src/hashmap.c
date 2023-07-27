#include <gmodule.h>
#include <glib.h>
#include <stdio.h>

typedef GHashTable* HashMap;

HashMap hm_create() {
	GHashTable* h = g_hash_table_new(g_str_hash, g_str_equal);
	return h;
}

const char* hm_get(HashMap hmap, const char* k) {
	printf("DEBUG in hm_get %s\n", k);
	return (const char*)g_hash_table_lookup(hmap, (gpointer)(k));
}

void hm_set(HashMap hmap, const char* k, const char* v) {
	printf("DEBUG in hm_set %s-%s\n", k, v);
	g_hash_table_insert(
		hmap,
		(gpointer)(k),
		(gpointer)(v)
	);
}

// int main () {
//     const char* k = "key";
//     const char* v = "value";

// 	HashMap h = hm_create();

// 	hm_set(h, k, v);
// 	const char* k1 = "asdasda";
// 	const char* v1 = hm_get(h, k1);

// 	if (v1 == NULL) {
// 		printf("Not Found.\n");
// 	} else {
// 		printf("%s\n", v1);
// 	}
// }