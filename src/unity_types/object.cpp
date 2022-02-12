#include "object.hpp"

void object::set_scripting_object() {
	m_scripting_object = memory::read<address_t>(m_address + O_OBJECT_SCRIPTING_OBJECT);
}

void object::set_scripting_class() {
	m_scripting_class = memory::read_chain(m_scripting_object, { 0x0, 0x0 });
}

void object::set_scripting_class_name() {
	m_scripting_class_name = memory::read_narrow_string(m_scripting_class + O_MONO_CLASS_NAME);
}

void object::set_scripting_class_namespace() {
	m_scripting_class_namespace = memory::read_narrow_string(m_scripting_class + O_MONO_CLASS_NAMESPACE);
}
