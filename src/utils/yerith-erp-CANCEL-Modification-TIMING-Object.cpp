/*
 * yerith-erp-CANCEL-Modification-TIMING-Object.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */


#include "yerith-erp-CANCEL-Modification-TIMING-Object.hpp"


#include "src/yerith-erp-windows.hpp"


#include "src/windows/yerith-erp-window-commons.hpp"




void YerithERPCancelModificationTimingObject::close_window_frame()
{
    if (0 != _window_frame_Pointer)
    {
        _window_frame_Pointer->stop_TIMER_Now();

        Set_Currently_performing_modifications(false);

        if (_window_frame_Pointer != _all_windows->_mainWindow)
        {
//            QDEBUG_STRING_OUTPUT_2_N("YerithERPCancelModificationTimingObject::close_window_frame; setVisible(false)",
//                                    _window_frame_Pointer->Get_YERITH_object_UOID());

            _window_frame_Pointer->setVisible(false);

            _window_frame_Pointer->update();
        }
    }
}



bool YerithERPCancelModificationTimingObject::yri_Cancel__ALL__modifications_On_This_Window_Frame_PAGE()
{
    if (get_closing_from_blanking_timing())
    {
        if (0 == _window_frame_Pointer)
        {
            return true;
        }

        if (___CLOSING_froM_bLanking_TIMING__count >= 1)
        {
            set_EXIT_anyway_THIS_window(true);

            set_closing_from_blanking_timing(false);

            close_window_frame();

            return true;
        }

        ___CLOSING_froM_bLanking_TIMING__count =
            ___CLOSING_froM_bLanking_TIMING__count + 1;
    }
    else
    {
        if (! get_closing_from_blanking_timing())
        {
            if (QMessageBox::Cancel ==
                    YerithQMessageBox::question(_window_frame_Pointer,
                                                get_Window__MODIFICATION_CANCELLATION_TITLE(),
                                                get_First__MODIFICATION_CANCELLATION_MESSAGE(),
                                                QMessageBox::Cancel,
                                                QMessageBox::Ok))
            {
                if (_window_frame_Pointer == _all_windows->_entrerWindow)
                {
                    YERITH_RUNTIME_VERIFIER_instrumentation_SELECT("stocks.yri_Cancel_INPUT",
                                                                   "src/utils/yerith-erp-CANCEL-Modification-TIMING-Object.cpp",
                                                                   77,
                                                                   _all_windows);
                }

                set_EXIT_anyway_THIS_window(false);
            }
            else
            {
                YerithQMessageBox::information(_window_frame_Pointer,
                                               get_Window__MODIFICATION_CANCELLATION_TITLE(),
                                               Get_Acceptation_Confirmation__MODIFICATION_CANCELLATION_MESSAGE(),
                                               QMessageBox::Ok);

                if (_window_frame_Pointer == _all_windows->_entrerWindow)
                {
                    YERITH_RUNTIME_VERIFIER_instrumentation_SELECT("stocks.yri_Cancel_INPUT",
                                                                   "src/utils/yerith-erp-CANCEL-Modification-TIMING-Object.cpp",
                                                                   94,
                                                                   _all_windows);
                }

                set_EXIT_anyway_THIS_window(true);
            }
        }
    }

    return true;
}
