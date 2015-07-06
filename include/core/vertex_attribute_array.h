/*
 * vertex_attribute_array.h
 *
 *  Created on: 29.12.2014
 *      Author: scones
 */

#ifndef INCLUDE_VERTEX_ATTRIBUTE_ARRAY_H_
#define INCLUDE_VERTEX_ATTRIBUTE_ARRAY_H_


namespace core {

	class vertex_attribute_array {
		public:


		vertex_attribute_array(unsigned int layout_id);
		~vertex_attribute_array();


		protected:


		unsigned int m_id;
	};

}


#endif /* INCLUDE_VERTEX_ATTRIBUTE_ARRAY_H_ */

