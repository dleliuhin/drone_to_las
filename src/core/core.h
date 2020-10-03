/*! \file core.h
 * \brief Core class interface.
 *
 * Class for algorithmic message processing.
 *
 * \authors Dmitrii Leliuhin
 * \date July 2020
 */

//=======================================================================================

#pragma once

#include "config.h"
#include "pack.h"

#include "vsignal.h"

//=======================================================================================
/*! \class Core
 * \brief Cascading data processing
 */
class Core
{
public:

    /*!
     * \param[in] conf Configuration settings.
     * \details Initialize _zcm node.
     */
    Core( const Config& conf = {} );

    //! \brief default destructor.
    ~Core() = default;

    //-----------------------------------------------------------------------------------

    /*! \fn void run( const Pack& pack );
     * \brief Run data processing.
     * \param[in] pack Raw timestamp.
     */
    void run( const Pack& pack );

    //-----------------------------------------------------------------------------------

    /*!
     * \brief emit signal if pack processed.
     * \param int64_t Raw data timestamp.
     */
    vsignal<int64_t> processed;

#ifdef GUI
    /*! \brief Send data to visualizer.
     * \param Your parameter description.
     */
    vsignal</*Your parameter.*/> plot_data;
#endif

    //-----------------------------------------------------------------------------------

private:

    //! \brief Configuration parameters.
    Config _conf;

};
//=======================================================================================
