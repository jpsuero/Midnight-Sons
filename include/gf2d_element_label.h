#ifndef __GF2D_LABEL_ELEMENT_H__
#define __GF2D_LABEL_ELEMENT_H__

#include "gf2d_elements.h"

typedef enum
{
    LJ_Left,
    LJ_Center,
    LJ_Right
}LabelJustification;

typedef struct
{
    TextBlock text;     /**<the label text*/
    Color color;        /**<color for the text*/
    int style;          /**<which font style to use*/
    int justify;        /**<leaning left or right*/
}LabelElement;

/**
 * @brief make a new label element
 * @param text the label text
 * @param color the label text color
 * @param style the font style
 * @param justify the LabelJustification
 * @return NULL on error or a new label element
 */
LabelElement *gf2d_element_label_new_full(char *text,Color color,int style,int justify);

/**
 * @brief set an element to be the label provided
 * @param e the element to set
 * @param label the label to set it too
 */
void gf2d_element_make_label(Element *e,LabelElement *label);

#endif