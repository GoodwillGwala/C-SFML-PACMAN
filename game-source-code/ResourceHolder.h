/**
*@class <ResourceHolder>
*@brief This class provides the interface for managing game resources
*/

#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

template <typename Resource, typename Identifier>
class ResourceHolder
{
	public:
		/**
        * @brief function that provides the interface for loading a resource
        * @param Indentity of resource and the filename including the file location
        */
		void            load(Identifier id, const std::string& filename);
		/**
        * @brief function that provides the interface for retrieving a resource
        * @param Indentity of resource
        * @return resource
        */
		Resource&       get(Identifier id);

		const Resource&	get(Identifier id) const;


	private:
		void insertResource(Identifier id, std::unique_ptr<Resource> resource);


	private:
		std::map<Identifier, std::unique_ptr<Resource>>	mResourceMap;
};
#include "ResourceHolder.inl"
#endif
