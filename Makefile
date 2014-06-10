drupal_version = 7.27

#
# Mysql db access
#
db_name = drupal
db_user = root
db_pass = 1234


help:
	@echo
	@echo "Mica Drupal 7 Client"
	@echo
	@echo "Available make targets:"
	@echo "  all          : Clean & setup Drupal with a symlink to Mica modules in target directory and import drupal.sql"
	@echo "  setup-drupal : Setup Drupal with Mica modules in target directory"
	@echo

all: clean setup-drupal wwww import-sql settings enable-mica devel cc

clean:
	rm -rf target

setup-drupal:
	drush make --prepare-install drupal/dev/drupal-basic.make target/drupal && \
	chmod -R a+w target/drupal/sites/default && \
	ln -s $(CURDIR)/drupal/modules/mica_client $(CURDIR)/target/drupal/sites/all/modules/mica_client

wwww:
	sudo ln -s $(CURDIR)/target/drupal /var/www/html/drupal && \
	sudo chown -R www-data:www-data /var/www/html/drupal

dump-sql:
	mysqldump -u $(db_user) --password=$(db_pass) --hex-blob $(db_name) --result-file="drupal/dev/drupal-$(drupal_version).sql"

import-sql:
	mysql -u $(db_user) --password=$(db_pass) -e "drop database $(db_name); create database $(db_name);"
	mysql -u $(db_user) --password=$(db_pass) $(db_name) < "drupal/dev/drupal-$(drupal_version).sql"

settings:
	cp drupal/dev/settings.php target/drupal/sites/default
	cp drupal/dev/.htaccess target/drupal
	cp -R drupal/libraries target/drupal/sites/all/

enable-mica:
	cd target/drupal && \
	drush en -y mica_study

devel:
	cd target/drupal && \
	drush dl devel && \
	drush en -y devel

cc:
	cd target/drupal && drush cc all
	
