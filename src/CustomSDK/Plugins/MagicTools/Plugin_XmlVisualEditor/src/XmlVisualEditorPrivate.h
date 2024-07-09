#pragma once

#ifndef __XMLVISUALEDITORPRIVATE_H__
# define __XMLVISUALEDITORPRIVATE_H__

#include <pugixml.hpp>

struct XmlVisualEditorPrivate
{
  pugi::xml_document xml_document;
};

#endif // !__XMLVISUALEDITORPRIVATE_H__
