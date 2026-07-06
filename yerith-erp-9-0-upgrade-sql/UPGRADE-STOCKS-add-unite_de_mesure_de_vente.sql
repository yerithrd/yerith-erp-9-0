ALTER TABLE achats ADD column unite_de_mesure_de_Vente int(3) AFTER enregistreur_stock;
ALTER TABLE marchandises ADD column unite_de_mesure_de_Vente int(3) AFTER nom_entreprise_client;
ALTER TABLE stocks ADD column unite_de_mesure_de_Vente int(3) AFTER is_service;
ALTER TABLE stocks_vendu ADD column unite_de_mesure_de_Vente int(3) AFTER is_service;
ALTER TABLE stocks_sorties ADD column unite_de_mesure_de_Vente int(3) AFTER is_service;
