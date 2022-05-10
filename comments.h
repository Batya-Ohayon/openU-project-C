#include "preprocessor.h"

/*the first demand of the text */
void delete_comments(FILE *, FILE *);

enum status {OUT, IN_STRING, LEFT_SLASH, IN_COMMENT, RIGHT_STAR};

