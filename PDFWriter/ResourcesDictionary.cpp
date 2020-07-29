/*
   Source File : ResourcesDictionary.cpp


   Copyright 2011 Gal Kahana PDFWriter

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

   
*/
#include "ResourcesDictionary.h"
#include "BoxingBase.h"
#include "PDFImageXObject.h"
#include <string>
#ifdef _WIN32
#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#else
#include "time.h"
#endif

typedef BoxingBaseWithRW<unsigned long> ULong;

ResourcesDictionary::ResourcesDictionary(void)
{
    mImageXObjectsCount = 0;
    mFormXObjectsCount = 0;
    mGenericXObjectsCount = 0;
    mExtGStatesCount = 0;
	mFontsCount = 0;
    mColorSpacesCount = 0;
    mPatternsCount = 0;
    mPropertiesCount = 0;
    mShadingCount = 0;

    mRandID = "_" + generateRandomString(3) + "_";

}
ResourcesDictionary::~ResourcesDictionary(void)
{
}

void ResourcesDictionary::AddProcsetResource(const std::string& inResourceName)
{
	if(mProcsets.find(inResourceName) == mProcsets.end())
		mProcsets.insert(inResourceName);
}

SingleValueContainerIterator<StringSet> ResourcesDictionary::GetProcesetsIterator()
{
	return SingleValueContainerIterator<StringSet>(mProcsets);
}

static const std::string scFM = "Fm";
std::string ResourcesDictionary::AddFormXObjectMapping(ObjectIDType inFormXObjectID)
{
    if(inFormXObjectID == 0)
    {
        std::string newName;
        do{
            newName = scFM + mRandID + ULong(mFormXObjectsCount+1).ToString();
            ++mFormXObjectsCount;
        }while(isLabelAlreadyUsed(newName,mXObjects));

        return newName;
    }
    else 
    {
        ObjectIDTypeToStringMap::iterator it = mXObjects.find(inFormXObjectID);

        if(it == mXObjects.end())
        {
            std::string newName;
            do{
                newName = scFM + mRandID + ULong(mFormXObjectsCount+1).ToString();
                ++mFormXObjectsCount;
            }while(isLabelAlreadyUsed(newName,mXObjects));

            it = mXObjects.insert(ObjectIDTypeToStringMap::value_type(inFormXObjectID,newName)).first;
        }
        return it->second;
    }
}

void ResourcesDictionary::AddFormXObjectMapping(ObjectIDType inFormXObjectID,const std::string& inFormXObjectName)
{
	ObjectIDTypeToStringMap::iterator it = mXObjects.find(inFormXObjectID);

	if(it == mXObjects.end())
		mXObjects.insert(ObjectIDTypeToStringMap::value_type(inFormXObjectID,inFormXObjectName));
	else
		it->second = inFormXObjectName;
}

static const std::string scIM = "Im";
std::string ResourcesDictionary::AddImageXObjectMapping(PDFImageXObject* inImageXObject)
{
	ObjectIDTypeToStringMap::iterator it = mXObjects.find(inImageXObject->GetImageObjectID());

	if(it == mXObjects.end())
	{
		std::string newName;
		do{
		    newName = scIM + mRandID + ULong(mImageXObjectsCount+1).ToString();
            ++mImageXObjectsCount;
		}while(isLabelAlreadyUsed(newName, mXObjects));

		AddImageXObjectMappingWithName(inImageXObject,newName);
		return newName;
	}
	else
	{
		return it->second;
	}
}

void ResourcesDictionary::AddImageXObjectMappingWithName(PDFImageXObject* inImageXObject, const std::string& inImageXObjectName)
{
	mXObjects.insert(ObjectIDTypeToStringMap::value_type(inImageXObject->GetImageObjectID(),inImageXObjectName));
	
	StringList::const_iterator it = inImageXObject->GetRequiredProcsetResourceNames().begin();
	for(; it != inImageXObject->GetRequiredProcsetResourceNames().end();++it)
	{
		if(it->size() > 0)
			AddProcsetResource(*it);
	}
}


void ResourcesDictionary::AddImageXObjectMapping(PDFImageXObject* inImageXObject, const std::string& inImageXObjectName)
{
	ObjectIDTypeToStringMap::iterator it = mXObjects.find(inImageXObject->GetImageObjectID());

	if(it == mXObjects.end())
		AddImageXObjectMappingWithName(inImageXObject,inImageXObjectName);
	else
		it->second = inImageXObjectName;
}

static const std::string scGS = "GS";
std::string ResourcesDictionary::AddExtGStateMapping(ObjectIDType inExtGStateID)
{
    if(inExtGStateID == 0)
    {
        std::string newName;
        do{
            newName = scGS + mRandID + ULong(mExtGStatesCount+1).ToString();
            ++mExtGStatesCount;
        }while(isLabelAlreadyUsed(newName, mExtGStates));

        return newName;
    }
    else 
    {
        ObjectIDTypeToStringMap::iterator it = mXObjects.find(inExtGStateID);
        
        if(it == mXObjects.end())
        {
            std::string newName;
            do{
                newName = scGS + mRandID + ULong(mExtGStatesCount+1).ToString();
                ++mExtGStatesCount;
            }while(isLabelAlreadyUsed(newName, mExtGStates));

            it = mExtGStates.insert(ObjectIDTypeToStringMap::value_type(inExtGStateID,newName)).first;
        }
        return it->second;
    }
}

void ResourcesDictionary::AddExtGStateMapping(ObjectIDType inExtGStateID, const std::string& inExtGStateName)
{
	ObjectIDTypeToStringMap::iterator it = mExtGStates.find(inExtGStateID);

	if(it == mExtGStates.end())
		mExtGStates.insert(ObjectIDTypeToStringMap::value_type(inExtGStateID,inExtGStateName));
	else
		it->second = inExtGStateName;
}


MapIterator<ObjectIDTypeToStringMap> ResourcesDictionary::GetExtGStatesIterator()
{
	return MapIterator<ObjectIDTypeToStringMap>(mExtGStates);
}

std::string ResourcesDictionary::AddImageXObjectMapping(ObjectIDType inImageXObjectID)
{
    if(inImageXObjectID == 0)
    {
        std::string newName;
        do{
            newName = scIM + mRandID + ULong(mImageXObjectsCount+1).ToString();
            ++mImageXObjectsCount;
        }while(isLabelAlreadyUsed(newName, mXObjects));

        return newName;
    }
    else 
    {
        ObjectIDTypeToStringMap::iterator it = mXObjects.find(inImageXObjectID);
        
        if(it == mXObjects.end())
        {
            std::string newName;
            do{
                newName = scIM + mRandID + ULong(mImageXObjectsCount+1).ToString();
                ++mImageXObjectsCount;
            }while(isLabelAlreadyUsed(newName, mXObjects));

            it = mXObjects.insert(ObjectIDTypeToStringMap::value_type(inImageXObjectID,newName)).first;
        }
        return it->second;
    }
}

void ResourcesDictionary::AddImageXObjectMapping(ObjectIDType inImageXObjectID, const std::string& inImageXObjectName)
{
	ObjectIDTypeToStringMap::iterator it = mXObjects.find(inImageXObjectID);

	if(it == mXObjects.end())
		mXObjects.insert(ObjectIDTypeToStringMap::value_type(inImageXObjectID,inImageXObjectName));
	else
		it->second = inImageXObjectName;
}

static const std::string scFN = "FN";
std::string ResourcesDictionary::AddFontMapping(ObjectIDType inFontObjectID)
{
    if(inFontObjectID == 0)
    {
        std::string newName ;
        do{
            newName = scFN + mRandID + ULong(mFontsCount+1).ToString();
            ++mFontsCount;
        }while(isLabelAlreadyUsed(newName, mFonts));

        return newName;
    }
    else 
    {
        ObjectIDTypeToStringMap::iterator it = mFonts.find(inFontObjectID);
        
        if(it == mFonts.end())
        {
            std::string newName;
            do{
                newName = scFN + mRandID + ULong(mFontsCount+1).ToString();
                ++mFontsCount;
            }while(isLabelAlreadyUsed(newName, mFonts));

            it = mFonts.insert(ObjectIDTypeToStringMap::value_type(inFontObjectID,newName)).first;
        }
        return it->second;
    }
}

void ResourcesDictionary::AddFontMapping(ObjectIDType inFontObjectID,const std::string& inFontObjectName)
{
	ObjectIDTypeToStringMap::iterator it = mFonts.find(inFontObjectID);

	if(it == mFonts.end())
		mFonts.insert(ObjectIDTypeToStringMap::value_type(inFontObjectID,inFontObjectName));
	else
		it->second = inFontObjectName;
}


MapIterator<ObjectIDTypeToStringMap> ResourcesDictionary::GetFontsIterator()
{
	return MapIterator<ObjectIDTypeToStringMap>(mFonts);
}

// Color space
static const std::string scCS = "CS";
std::string ResourcesDictionary::AddColorSpaceMapping(ObjectIDType inColorspaceID)
{
    if(inColorspaceID == 0)
    {
        std::string newName;
        do{
            newName = scCS + mRandID + ULong(mColorSpacesCount+1).ToString();
            ++mColorSpacesCount;
        }while(isLabelAlreadyUsed(newName, mColorSpaces));

        return newName;
    }
    else 
    {
        ObjectIDTypeToStringMap::iterator it = mColorSpaces.find(inColorspaceID);
        
        if(it == mColorSpaces.end())
        {
            std::string newName;
            do{
                newName = scCS + mRandID + ULong(mColorSpacesCount+1).ToString();
                ++mColorSpacesCount;
            }while(isLabelAlreadyUsed(newName, mColorSpaces));

            it = mColorSpaces.insert(ObjectIDTypeToStringMap::value_type(inColorspaceID,newName)).first;
        }
        return it->second;
    }
}


MapIterator<ObjectIDTypeToStringMap> ResourcesDictionary::GetColorSpacesIterator()
{
	return MapIterator<ObjectIDTypeToStringMap>(mColorSpaces);
}

// Patterns
static const std::string scPT = "PT";
std::string ResourcesDictionary::AddPatternMapping(ObjectIDType inPatternID)
{
    if(inPatternID == 0)
    {
        std::string newName;
        do{
            newName = scPT + mRandID + ULong(mPatternsCount+1).ToString();
            ++mPatternsCount;
        }while(isLabelAlreadyUsed(newName, mPatterns));

        return newName;
    }
    else 
    {
        ObjectIDTypeToStringMap::iterator it = mPatterns.find(inPatternID);
        
        if(it == mPatterns.end())
        {
            std::string newName;
            do{
                newName = scPT + mRandID + ULong(mPatternsCount+1).ToString();
                ++mPatternsCount;
            }while(isLabelAlreadyUsed(newName, mPatterns));

            it = mPatterns.insert(ObjectIDTypeToStringMap::value_type(inPatternID,newName)).first;
        }
        return it->second;
    }
}


MapIterator<ObjectIDTypeToStringMap> ResourcesDictionary::GetPatternsIterator()
{
	return MapIterator<ObjectIDTypeToStringMap>(mPatterns);
}


// Properties
static const std::string scPP = "PP";
std::string ResourcesDictionary::AddPropertyMapping(ObjectIDType inPropertyID)
{
    if(inPropertyID == 0)
    {
        std::string newName;
        do{
            newName = scPP + mRandID + ULong(mPropertiesCount+1).ToString();
            ++mPropertiesCount;
        }while(isLabelAlreadyUsed(newName, mProperties));

        return newName;
    }
    else 
    {
        ObjectIDTypeToStringMap::iterator it = mProperties.find(inPropertyID);
        
        if(it == mProperties.end())
        {
            std::string newName;
            do{
                newName = scPP + mRandID + ULong(mPropertiesCount+1).ToString();
                ++mPropertiesCount;
            }while(isLabelAlreadyUsed(newName, mProperties));
            it = mProperties.insert(ObjectIDTypeToStringMap::value_type(inPropertyID,newName)).first;
        }
        return it->second;
    }
}


MapIterator<ObjectIDTypeToStringMap> ResourcesDictionary::GetPropertiesIterator()
{
	return MapIterator<ObjectIDTypeToStringMap>(mProperties);
}

// Generic XObjects
static const std::string scXO = "XO";
std::string ResourcesDictionary::AddXObjectMapping(ObjectIDType inXObjectID)
{
    if(inXObjectID == 0)
    {
        std::string newName;
        do{
            newName = scXO + mRandID + ULong(mGenericXObjectsCount+1).ToString();
            ++mGenericXObjectsCount;
        }while(isLabelAlreadyUsed(newName, mXObjects));

        return newName;
    }
    else 
    {
        ObjectIDTypeToStringMap::iterator it = mXObjects.find(inXObjectID);
        
        if(it == mXObjects.end())
        {
            std::string newName;
            do{
                newName = scXO + mRandID + ULong(mGenericXObjectsCount+1).ToString();
                ++mGenericXObjectsCount;
            }while(isLabelAlreadyUsed(newName, mXObjects));

            it = mXObjects.insert(ObjectIDTypeToStringMap::value_type(inXObjectID,newName)).first;
        }
        return it->second;
    }
}


MapIterator<ObjectIDTypeToStringMap> ResourcesDictionary::GetXObjectsIterator()
{
	return MapIterator<ObjectIDTypeToStringMap>(mXObjects);
}

// Shading
static const std::string scSH = "SH";
std::string ResourcesDictionary::AddShadingMapping(ObjectIDType inShadingID)
{
    if(inShadingID == 0)
    {
        std::string newName;
        do{
            newName = scSH + mRandID + ULong(mShadingCount+1).ToString();
            ++mShadingCount;
        }while(isLabelAlreadyUsed(newName, mShading));

        return newName;
    }
    else 
    {
        ObjectIDTypeToStringMap::iterator it = mShading.find(inShadingID);
        
        if(it == mShading.end())
        {
            std::string newName;
            do{
                newName = scSH + mRandID + ULong(mShadingCount+1).ToString();
                ++mShadingCount;
            }while(isLabelAlreadyUsed(newName, mShading));

            it = mShading.insert(ObjectIDTypeToStringMap::value_type(inShadingID,newName)).first;
        }
        return it->second;
    }
}

MapIterator<ObjectIDTypeToStringMap> ResourcesDictionary::GetShadingsIterator()
{
	return MapIterator<ObjectIDTypeToStringMap>(mShading);
}

// Check if label is in use
bool ResourcesDictionary::isLabelAlreadyUsed(std::string &label, ObjectIDTypeToStringMap &map){
    for(auto iterator : map){
        if(iterator.second == label){
            return true;
        }
    }
    return false;
}

// Generate random ID for names
std::string ResourcesDictionary::generateRandomString(size_t length){
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    int stringLength = sizeof(alphanum) - 1;
#ifdef _WIN32
    auto now = std::chrono::high_resolution_clock::now();
    auto seed = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    srand(seed);
#else
    srand(time(0));
#endif
    std::string randString;
    for(unsigned int i = 0; i < length; i++)
    {
        randString += alphanum[rand() % stringLength];

    }
    return randString;
}
