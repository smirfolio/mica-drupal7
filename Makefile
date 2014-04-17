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
	@echo "  all          : Clean & setup Drupal with Mica modules in target directory"
	@echo "  setup-drupal : Setup Drupal with Mica modules in target directory"
	@echo "  copy-mica    : Copy Mica modules to Drupal instance in target directory"
	@echo

all: clean setup-drupal

clean:
	rm -rf target

setup-drupal:
	drush make --prepare-install drupal/drupal-basic.make target/drupal && \
	chmod -R a+w target/drupal/sites/default && \
	ln -s $(CURDIR)/drupal/modules/mica_client $(CURDIR)/target/drupal/sites/all/modules/mica_client

copy-mica:
	cp -r drupal/modules/* target/drupal/sites/all/modules

wwww:
	ln -s $(CURDIR)/target/drupal /var/www/drupal

dump-sql:
	mysqldump -u $(db_user) --password=$(db_pass) --hex-blob $(db_name) --result-file="drupal/drupal-$(drupal_version).sql"

import-sql:
	mysql -u $(db_user) --password=$(db_pass) -e "drop database $(db_name); create database $(db_name);"
	mysql -u $(db_user) --password=$(db_pass) $(db_name) < "drupal/drupal-$(drupal_version).sql"
