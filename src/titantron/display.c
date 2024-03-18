#include "main.h"
LV_IMG_DECLARE(titantronlogo);
void teamLogo(){
    lv_obj_t * img = lv_img_create(lv_scr_act(),NULL);
    lv_img_set_src(img, &titantronlogo);
    lv_obj_align(img, NULL, LV_ALIGN_CENTER, 0, 0);

}