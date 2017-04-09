#ifndef _UMLSETTINGS_H
#define _UMLSETTINGS_H


#include "misc/mystr.h"
#include "aLanguage.h"

struct UmlBuiltin;
struct UmlStereotype;

// This class manages settings not linked with a language, configured through
// the 'Generation settings' dialog.
//
// This class may be defined as a 'singleton', but I prefer to use static
// members allowing to just write 'UmlSettings::member' rather than
// 'UmlSettings::instance()->member' or other long sentence like this.

class UmlSettings
{
public:
    // return the default description
    static WrapperStr artifactDescription();

    // set the default description
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ArtifactDescription(WrapperStr v);

    // return the default description
    static WrapperStr classDescription();

    // set the default description
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ClassDescription(WrapperStr v);

    // return the default description
    static WrapperStr operationDescription();

    // set the default description
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_OperationDescription(WrapperStr v);

    // return the default description
    static WrapperStr attributeDescription();

    // set the default description
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_AttributeDescription(WrapperStr v);

    // return the default description
    static WrapperStr relationDescription();

    // set the default description
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationDescription(WrapperStr v);

    // return the language from which the getter's name rule must be followed at Uml level
    static aLanguage umlGetName();

    // set the language from which the getter's name rule must be followed at Uml level
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_UmlGetName(aLanguage v);

    // return the language from which the setter's name rule must be followed at Uml level
    static aLanguage umlSetName();

    // set the language from which the setter's name rule must be followed at Uml level
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_UmlSetName(aLanguage v);


protected:
    // never called !
    UmlSettings() {};

    static bool _defined;


private:
    static aLanguage _uml_get_name;

    static aLanguage _uml_set_name;


protected:
    static WrapperStr _artifact_default_description;

    static WrapperStr _class_default_description;

    static WrapperStr _operation_default_description;

    static WrapperStr _attribute_default_description;

    static WrapperStr _relation_default_description;

    static QHash<QString,UmlBuiltin*> _map_builtins;

    static UmlBuiltin * _builtins;

    static QHash<QString,UmlStereotype*> _map_relation_attribute_stereotypes;

    static UmlStereotype * _relation_attribute_stereotypes;

    static QHash<QString,UmlStereotype*> _map_class_stereotypes;

    static UmlStereotype * _class_stereotypes;

    static void read_();

    static void read_if_needed_();

    static unsigned multiplicity_column(const WrapperStr & mult);

    static WrapperStr uml_type(const WrapperStr & t, WrapperStr UmlBuiltin::* f);

    static WrapperStr uml_rel_attr_stereotype(const WrapperStr & t, WrapperStr UmlStereotype::* f);

    static WrapperStr uml_class_stereotype(const WrapperStr & t, WrapperStr UmlStereotype::* f);

    static UmlBuiltin * add_type(const WrapperStr & s);

    static UmlStereotype * add_rel_attr_stereotype(const WrapperStr & s);

    static UmlStereotype * add_class_stereotype(const WrapperStr & s);

};

#endif
