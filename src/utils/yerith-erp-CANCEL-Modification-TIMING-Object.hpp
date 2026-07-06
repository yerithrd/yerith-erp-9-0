/*
 * yerith-erp-CANCEL-Modification-TIMING-Object.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef _SRC_YERITH_CANCEL_MODIFICATION_TIMING_OBJECT_HPP_
#define _SRC_YERITH_CANCEL_MODIFICATION_TIMING_OBJECT_HPP_

#include "src/include/yerith-erp-9-0-software.text-configuration.hpp"

#include "src/utils/yerith-erp-utils.hpp"


#include <QtCore/QDate>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QTextStream>


class YerithERPWindows;

class YerithWindowsCommons;



class YerithERPCancelModificationTimingObject : public QObject
{
    Q_OBJECT

public:

    YERITH_CLASS_OPERATORS

    inline YerithERPCancelModificationTimingObject(YerithERPWindows     *all_windows,
                                                   YerithWindowsCommons *a_window_frame_Pointer)
    :_all_windows(all_windows),
     _window_frame_Pointer(a_window_frame_Pointer),
     ___key_pressed_TO_eliminate___CLOSING_froM_bLanking_TIMING(false),
     ___CLOSING_froM_bLanking_TIMING(false),
     ___Currently_performing_modifications(false),
     ___EXIT_anyway_THIS_window(false),
     ___CLOSING_froM_bLanking_TIMING__count(0)
    {
    }

    inline YerithERPCancelModificationTimingObject(YerithERPWindows     *all_windows,
                                                   YerithWindowsCommons *a_window_frame_Pointer,
                                                   QString a_Window__MODIFICATION_CANCELLATION_TITLE)
    :_all_windows(all_windows),
     _window_frame_Pointer(a_window_frame_Pointer),
     _Window__MODIFICATION_CANCELLATION_TITLE(a_Window__MODIFICATION_CANCELLATION_TITLE),
     ___key_pressed_TO_eliminate___CLOSING_froM_bLanking_TIMING(false),
     ___CLOSING_froM_bLanking_TIMING(false),
     ___Currently_performing_modifications(false),
     ___EXIT_anyway_THIS_window(false),
     ___CLOSING_froM_bLanking_TIMING__count(0)
    {
    }

    virtual inline ~YerithERPCancelModificationTimingObject()
    {
    }


    void close_window_frame();


    bool yri_Cancel__ALL__modifications_On_This_Window_Frame_PAGE();


    /**
     * Accessors and Modificator for member variable
     * '_Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE'
     */
    inline void set_window_frame_pointer(YerithWindowsCommons *a_window_frame_Pointer)
    {
        _window_frame_Pointer = a_window_frame_Pointer;
    }

    inline YerithWindowsCommons *get_window_frame_pointer()
    {
        return _window_frame_Pointer;
    }


    /**
     * Accessors and Modificator for member variable
     * '_Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE'
     */
    inline void Set_Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE(QString a_message)
    {
        _Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE = a_message;
    }

    inline QString Get_Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE()
    {
        return _Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE;
    }


    /**
     * Accessors and Modificator for member variable
     * '_Window__MODIFICATION_CANCELLATION_TITLE'
     */
    inline void Set_Window__MODIFICATION_CANCELLATION_TITLE(QString a_Window__MODIFICATION_CANCELLATION_TITLE)
    {
        _Window__MODIFICATION_CANCELLATION_TITLE =
            a_Window__MODIFICATION_CANCELLATION_TITLE;
    }

    inline QString get_Window__MODIFICATION_CANCELLATION_TITLE()
    {
        return _Window__MODIFICATION_CANCELLATION_TITLE;
    }


    inline void Set_Currently_performing_modifications(bool currently_performing_modifications)
    {
        ___Currently_performing_modifications =
            currently_performing_modifications;
    }

    inline bool Is_Currently_performing_modifications()
    {
        return ___Currently_performing_modifications;
    }


    /**
     * Accessors and Modificator for member variable
     * '_First__MODIFICATION_CANCELLATION_MESSAGE'
     */
    inline void set_First__MODIFICATION_CANCELLATION_MESSAGE(QString a_message)
    {
        _First__MODIFICATION_CANCELLATION_MESSAGE = a_message;
    }

    inline QString get_First__MODIFICATION_CANCELLATION_MESSAGE()
    {
        return _First__MODIFICATION_CANCELLATION_MESSAGE;
    }



    inline void Set_key_pressed_TO_eliminate___CLOSING_froM_bLanking_TIMING
                    (bool A__key_pressed_TO_eliminate___CLOSING_froM_bLanking_TIMING)
    {
        ___key_pressed_TO_eliminate___CLOSING_froM_bLanking_TIMING =
                A__key_pressed_TO_eliminate___CLOSING_froM_bLanking_TIMING;
    }

    inline bool Get_key_pressed_TO_eliminate___CLOSING_froM_bLanking_TIMING()
    {
        return ___key_pressed_TO_eliminate___CLOSING_froM_bLanking_TIMING;
    }



    inline void set_closing_from_blanking_timing(bool a_closing_from_blanking_timing)
    {
        ___CLOSING_froM_bLanking_TIMING = a_closing_from_blanking_timing;
    }

    inline bool get_closing_from_blanking_timing()
    {
        return ___CLOSING_froM_bLanking_TIMING;
    }



    inline void set_EXIT_anyway_THIS_window(bool a_bool_exit_anyway_THIS_window)
    {
        ___EXIT_anyway_THIS_window = a_bool_exit_anyway_THIS_window;
    }

    inline bool EXIT_anyway_THIS_window()
    {
        return ___EXIT_anyway_THIS_window;
    }


private:

    YerithERPWindows     *_all_windows;

    YerithWindowsCommons *_window_frame_Pointer;

    QString _Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE;

    QString _Window__MODIFICATION_CANCELLATION_TITLE;

    QString _First__MODIFICATION_CANCELLATION_MESSAGE;


    bool    ___key_pressed_TO_eliminate___CLOSING_froM_bLanking_TIMING;

    bool    ___CLOSING_froM_bLanking_TIMING;


    bool    ___Currently_performing_modifications;

    bool    ___EXIT_anyway_THIS_window;

    uint    ___CLOSING_froM_bLanking_TIMING__count;

};

#endif /* _SRC_YERITH_CANCEL_MODIFICATION_TIMING_OBJECT_HPP_ */
