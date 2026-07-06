
bool YerithAdminCreateWindow::creer_localisation()
{
    emit SIGNAL_INCREMENT_PROGRESS_BAR(5);

    if (creer_localisation_check_fields())
    {
        QString retMsg = QObject::tr("La localisation '%1'")
                           .arg(lineEdit_creer_localisation_nom->text());

        YerithSqlTableModel &localisationsTableModel =
                        _allWindows->getSqlTableModel_localisations();

        localisationsTableModel
            .yerithSetFilter_WITH_where_clause(QString("LOWER(%1) = LOWER('%2')")
                                                .arg(YerithDatabaseTableColumn::NOM_LOCALISATION,
                                                     lineEdit_creer_localisation_nom->text()));

        //qDebug() << "++ filter: " << localisationsTableModel.filter();

        int localisationsTableModelRowCount =
                        localisationsTableModel.easySelect();

        if (localisationsTableModelRowCount > 0)
        {
            QSqlRecord record = localisationsTableModel.record(0);

            QString duplicateLocalisation =
                        GET_SQL_RECORD_DATA(record,
                                            YerithDatabaseTableColumn::NOM_ENTREPRISE);

            //qDebug() << "++ duplicate localisation: " << duplicateLocalisation;

            retMsg.append(QObject::tr("%1' existe déjà !").arg
                          (duplicateLocalisation));

            YerithQMessageBox::warning(this,
                                       QObject::tr
                                       ("Yerith-pgi-9.0 ~ administration ~ créer ~ localisation"),
                                       retMsg);

            localisationsTableModel.resetFilter("src/admin/creer/creer-localisation.cpp",
                                                 42);


            emit SIGNAL_INCREMENT_PROGRESS_BAR(20);


            return false;
        }


        localisationsTableModel
			.resetFilter("src/admin/creer/creer-localisation.cpp",
        				 47);


        QSqlRecord record = localisationsTableModel.record();

        record.setValue(YerithDatabaseTableColumn::ID,
                        YerithERPWindows::getNextIdSqlTableModel_localisations());

        record.setValue(YerithDatabaseTableColumn::NUMERO_UNIQUE,
                        lineEdit_creer_localisation_numero_unique->text());

        record.setValue(YerithDatabaseTableColumn::ADRESSE_IP,
                        comboBox_label_creer_localisation_adresse_ip->currentText());

        record.setValue(YerithDatabaseTableColumn::NOM_LOCALISATION,
                        lineEdit_creer_localisation_nom->text());

        record.setValue(YerithDatabaseTableColumn::QUARTIER,
                        lineEdit_creer_localisation_quartier->text());

        record.setValue(YerithDatabaseTableColumn::VILLE,
                        lineEdit_creer_localisation_ville->text());

        record.setValue(YerithDatabaseTableColumn::PROVINCE_ETAT,
                        lineEdit_creer_localisation_province_etat->text());

        record.setValue(YerithDatabaseTableColumn::PAYS,
                        lineEdit_creer_localisation_pays->text());

        record.setValue(YerithDatabaseTableColumn::BOITE_POSTALE,
                        lineEdit_creer_localisation_boite_postale->text());

        record.setValue("date_ouverture",
                        dateEdit_creer_localisation_date_ouverture->date());

        record.setValue(YerithDatabaseTableColumn::EMAIL,
                        lineEdit_creer_localisation_email->text());

        record.setValue(YerithDatabaseTableColumn::NUMERO_TELEPHONE_1,
                        lineEdit_creer_localisation_numero_telephone_1->text());

        record.setValue(YerithDatabaseTableColumn::NUMERO_TELEPHONE_2,
                        lineEdit_creer_localisation_numero_telephone_2->text());

        record.setValue("dbms",
                        comboBox_creer_localisation_base_donnees->currentText());

        record.setValue("description_lieu",
                        textEdit_creer_localisation_description_lieu->toPlainText());


        emit SIGNAL_INCREMENT_PROGRESS_BAR(75);

        QThread::sleep(1.0);


        bool success =
        		localisationsTableModel
					.insertNewRecord(record,
									 _allWindows->_adminCreateWindow,
									 "src/admin/creer/creer-localisation.cpp",
									 102,
									 lineEdit_creer_localisation_nom->text());


        if (!success)
        {
            retMsg.append(QObject::tr("' n'a pas pu être créer !"));

            YerithQMessageBox::warning(this,
                                       QObject::tr("Yerith-pgi-9.0 ~ administration ~ créer ~ localisation"),
                                       retMsg);
            return false;
        }


        QString current_entered_database_NAME_by_Admin = lineEdit_creer_localisation_nom->text();


        bool retMsg_already_sent_to_user = false;


        /*
         * In case IP address is locally hosted, create
         * a new local database for this customer
         * 'lineEdit_creer_localisation_nom->text()' !
         */
        if (! current_entered_database_NAME_by_Admin.isEmpty() &&
            YerithUtils::isEqualCaseInsensitive("127.0.0.1",
                                                comboBox_label_creer_localisation_adresse_ip->currentText()))
        {
//            QDEBUG_STRING_OUTPUT_1("! current_entered_database_NAME_by_Admin.isEmpty() Success !");

            QString create_database_query_Anew =
                        QString("CREATE DATABASE %1;")
                            .arg(current_entered_database_NAME_by_Admin);

            bool success_created_new_database_set =
                    YerithUtils::execQuery
                        (create_database_query_Anew);

            if (success_created_new_database_set)
            {
                _logger->log("YerithAdminCreateWindow::creer_localisation",
                              QString("\n"
                                      "\t\t New database (%1) set created for 'consultant' client.")
                                .arg(current_entered_database_NAME_by_Admin));


                retMsg = QString("A New database (%1) set created for 'consultant' client.")
                                .arg(current_entered_database_NAME_by_Admin);

                YerithQMessageBox::information(this,
                                               QObject::tr("Yerith-pgi-9.0 ~ administration ~ créer ~ localisation"),
                                               retMsg);


                retMsg_already_sent_to_user = true;



                if (! YerithDatabase::Create___Database__Tables___Localisation___INITIAL
                            (current_entered_database_NAME_by_Admin))
                {
                    _logger->log("YerithAdminCreateWindow::creer_localisation",
                                  QString("\n"
                                          "\t\t Please restart 'at least 3 times.' to create \n"
                                          "\t\t all database (of '%1') necessary tables.")
                                    .arg(current_entered_database_NAME_by_Admin));


                    retMsg = QString("Please restart 'at least 3 times.' to create \n"
                                     "all database ('%1') necessary tables.")
                                .arg(current_entered_database_NAME_by_Admin);


                    YerithQMessageBox::warning(this,
                                               QObject::tr("Yerith-pgi-9.0 ~ (Please restart 'at least 3 times.') "
                                                           "administration ~ créer ~ localisation"),
                                               retMsg);


                    QDEBUG_STRING_OUTPUT_1
                        (QString("Please restart 'at least 3 times.' to create all database ('%1') necessary tables.")
                            .arg(current_entered_database_NAME_by_Admin));
                }
            }
        }


        emit SIGNAL_INCREMENT_PROGRESS_BAR(90);


        QThread::sleep(1.0);


        retMsg.append(QObject::tr(" a été créer avec succès !"));


        if (! retMsg_already_sent_to_user)
        {
            YerithQMessageBox::information(this,
                                           QObject::tr("Yerith-pgi-9.0 ~ administration ~ créer ~ localisation"),
                                           retMsg);
        }


        clear_localisation_all_fields();

        _allWindows->_adminListerWindow->rendreVisible(SUJET_ACTION_LOCALISATION);

        rendreInvisible();
    }
    else
    {
        YerithQMessageBox::information(this,
                                       QObject::tr("Yerith-pgi-9.0 ~ administration ~ créer ~ localisation"),
                                       QObject::tr("BIEN VOULOIR REMPLIR TOUS LES "
                                                   "CHAMPS DE TEXTES OBLIGATOIRES !"));

        return false;
    }

    emit SIGNAL_INCREMENT_PROGRESS_BAR(98);

    return true;
}


void YerithAdminCreateWindow::populateLocalisationComboBoxes()
{
    _logger->log("populateAlerteComboBoxes");

    comboBox_creer_localisation_base_donnees->populateComboBoxRawString(YerithDatabase::DBMS, QString("nom_dbms"));

    comboBox_label_creer_localisation_adresse_ip->setYerithEditable(true);

    comboBox_label_creer_localisation_adresse_ip
        ->addItem(YerithUtils::EMPTY_STRING);

    comboBox_label_creer_localisation_adresse_ip
        ->populateComboBoxRawString_APPEND(YerithDatabase::LOCALISATIONS,
                                           YerithDatabaseTableColumn::ADRESSE_IP);

    comboBox_label_creer_localisation_adresse_ip
        ->addItem_AFTER_POPULATE("127.0.0.1");
}


void YerithAdminCreateWindow::clear_localisation_all_fields()
{
    comboBox_label_creer_localisation_adresse_ip->clearField();
    lineEdit_creer_localisation_numero_unique->clearField();
    lineEdit_creer_localisation_nom->clearField();
    lineEdit_creer_localisation_quartier->clearField();
    lineEdit_creer_localisation_ville->clearField();
    lineEdit_creer_localisation_province_etat->clearField();
    lineEdit_creer_localisation_pays->clearField();
    lineEdit_creer_localisation_boite_postale->clearField();
    dateEdit_creer_localisation_date_ouverture->reset();
    lineEdit_creer_localisation_email->clearField();
    lineEdit_creer_localisation_numero_telephone_1->clearField();
    lineEdit_creer_localisation_numero_telephone_2->clearField();
    textEdit_creer_localisation_description_lieu->clear();


    reset_window_widgets_modification_Bit____LOCALISATION();
}


