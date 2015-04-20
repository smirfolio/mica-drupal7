mica_current_tag = 1.0.0-dev
mica_branch_version=1.0.x
drupal_version = 7.34
mica_version=$(drupal_version)-$(mica_current_tag)
drupal_org_mica=git.drupal.org:project/obiba_mica.git
obiba-progressbar-version=1.0.0

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

include make-perform-release.mk

all: clean setup-drupal www import-sql settings bootstrap enable-mica enable-obiba-auth devel less-css jquery_update datatables obiba-progressbar cc

clean:
	rm -rf target

setup-drupal:
	drush make --prepare-install drupal/dev/drupal-basic.make target/drupal && \
	chmod -R a+w target/drupal && \
	ln -s $(CURDIR)/drupal/modules/obiba_mica $(CURDIR)/target/drupal/sites/all/modules/obiba_mica && \
	ln -s $(CURDIR)/drupal/themes/obiba_bootstrap $(CURDIR)/target/drupal/sites/all/themes/obiba_bootstrap && \
	git clone https://github.com/obiba/drupal7-auth.git $(CURDIR)/target/drupal/sites/all/modules/obiba_auth && \
	git clone https://github.com/obiba/drupal7-protobuf.git  $(CURDIR)/target/drupal/sites/all/modules/obiba_protobuf

www:
	sudo rm -f /var/www/html/drupal && \
	sudo ln -s $(CURDIR)/target/drupal /var/www/html/drupal && \
	sudo chown -R www-data:www-data /var/www/html/drupal

dump-sql:
	mysqldump -u $(db_user) --password=$(db_pass) --hex-blob $(db_name) --result-file="drupal/dev/drupal-$(drupal_version).sql"

create-sql:
	mysql -u $(db_user) --password=$(db_pass) -e "drop database if exists $(db_name); create database $(db_name);"

import-sql: create-sql
	mysql -u $(db_user) --password=$(db_pass) $(db_name) < "drupal/dev/drupal-$(drupal_version).sql"

settings:
	sed  's/@db_pass@/$(db_pass)/g' drupal/dev/settings.php > target/drupal/sites/default/settings.php
	cp drupal/dev/.htaccess target/drupal

enable-mica:
	cd target/drupal && \
	drush en -y obiba_mica

enable-obiba-auth:
	cd target/drupal && \
	drush en -y obiba_auth

cptp:
	cd target/drupal && \
	rm -rf sites/all/modules/cptp/ && \
	cp -r ~/Dropbox/P3G-OBiBa-Share/mlstr-seed/drupal/cptp sites/all/modules && \
	drush en -y cptp

bootstrap:
	cd target/drupal && \
	drush dl -y bootstrap && \
	drush en -y bootstrap && \
	drush en -y obiba_bootstrap && \
	drush vset -y theme_default obiba_bootstrap && \
	drush vset -y admin_theme seven

less-css:
	lessc $(CURDIR)/drupal/themes/obiba_bootstrap/less/style.less $(CURDIR)/drupal/themes/obiba_bootstrap/css/style.css
	lessc $(CURDIR)/drupal/themes/obiba_bootstrap/less/obiba.less $(CURDIR)/drupal/themes/obiba_bootstrap/css/obiba.css

jquery_update:
	cd target/drupal && \
	drush dl -y jquery_update && \
	drush en -y jquery_update && \
	drush vset -y jquery_update_jquery_version 1.8 && \
	drush vset -y jquery_update_jquery_admin_version 1.8

devel:
	cd target/drupal && \
	drush dl -y devel && \
	drush en -y devel

cas:
	cd target/drupal && \
	drush dl -y cas && \
	drush en -y cas

chart-enable:
	cd target/drupal && \
	drush highcharts-download && \
	drush en -y charts_highcharts

datatables: datatables-download datatables-plugins-download

datatables-download:
	cd target/drupal && \
	drush datatables-download


datatables-plugins-download:
	cd target/drupal && \
	drush datatables-plugins-download

obiba-progressbar:
	cd target/drupal && \
	drush vset -y obiba-progressbar-lib obiba-progressbar-$(obiba-progressbar-version) && \
	drush vset -y obiba-progressbar-file "dist/obiba-progressbar" && \
	drush obiba-progressbar-download $(obiba-progressbar-version);


cc:
	cd target/drupal && drush cc all
