#!/bin/bash

CLASS_NAME=$1
OUT_PATH=$2

[[ -z $CLASS_NAME ]] && echo -e "\e[44mEmpty arg CLASS_NAME\e[0m" && exit 1 
[[ -z $OUT_PATH ]] && echo -e "\e[44mEmpty arg OUT_PATH\e[0m" && exit 1

#----------------------------------------------------------------------------------------

lower_case=$(echo $CLASS_NAME | sed -r 's/([A-Z])/_\L\1/g' | sed 's/^_//')
upper_case=$(echo "${lower_case^^}")

#----------------------------------------------------------------------------------------

if [ -d $OUT_PATH/$lower_case ]; 
then
	echo "The $OUT_PATH/$lower_case directory already is." && exit 1
else
	mkdir -p $OUT_PATH/$lower_case
fi

#----------------------------------------------------------------------------------------

text=$(cat <<-END
#========================================================================================

include_directories( \${CMAKE_CURRENT_LIST_DIR} )

set( $upper_case
     \${CMAKE_CURRENT_LIST_DIR}/$lower_case.h
     \${CMAKE_CURRENT_LIST_DIR}/$lower_case.cpp
   )

#========================================================================================
END
)

touch $OUT_PATH/$lower_case/$lower_case.cmake
echo "$text" > $OUT_PATH/$lower_case/$lower_case.cmake

#----------------------------------------------------------------------------------------

text=$(cat <<-END
# $CLASS_NAME

Class description.

---

List of algorithms:
...

---
END
)

touch $OUT_PATH/$lower_case/README.md
echo "$text" > $OUT_PATH/$lower_case/README.md

#----------------------------------------------------------------------------------------

text=$(cat <<-END
/*! \file $lower_case.h
 * \brief $CLASS_NAME class interface.
 *
 * Class description.
 *
 * \authors $(echo "$USER")
 * \date $(echo $(LANG=en_us_88591; date +"%B %Y"))
 */

//=======================================================================================

#pragma once

#include "vsignal.h"

//=======================================================================================
/*! \class $CLASS_NAME
 * \brief Some briefing
 */
class $CLASS_NAME
{
public:

	//! \brief default constructor.    
    $CLASS_NAME() = default;

    //! \brief default destructor.
    ~$CLASS_NAME() = default;

    //-----------------------------------------------------------------------------------

    /*! \brief Emitter.
     * \param Your parameter description.
     */
    vsignal</*Your parameter.*/> emit;

    //-----------------------------------------------------------------------------------

private:

    //! List of private variables.

};
//=======================================================================================

END
)

touch $OUT_PATH/$lower_case/$lower_case.h
echo "$text" > $OUT_PATH/$lower_case/$lower_case.h

#----------------------------------------------------------------------------------------

text=$(cat <<-END
/*! \file $lower_case.cpp
 * \brief $CLASS_NAME class implementation.
 *
 * \authors $(echo "$USER")
 * \date $(echo $(LANG=en_us_88591; date +"%B %Y"))
 */

//=======================================================================================

#include "$lower_case.h"

END
)

touch $OUT_PATH/$lower_case/$lower_case.cpp
echo "$text" > $OUT_PATH/$lower_case/$lower_case.cpp

#----------------------------------------------------------------------------------------