#
#
#
#
datestamp=$(shell date +%s)
release_date=$(shell date -R)

inject-version-info:
	$(call inject-version-info,modules/,obiba_mica,$(mica_version))
	$(call inject-version-info,modules/obiba_mica,obiba_mica_commons,$(mica_version))
	$(call inject-version-info,modules/obiba_mica,obiba_mica_dataset,$(mica_version))
	$(call inject-version-info,modules/obiba_mica,obiba_mica_model,$(mica_version))
	$(call inject-version-info,modules/obiba_mica,obiba_mica_network,$(mica_version))
	$(call inject-version-info,modules/obiba_mica,obiba_mica_search,$(mica_version))
	$(call inject-version-info,modules/obiba_mica,obiba_mica_study,$(mica_version))
	$(call inject-version-info,modules/obiba_mica,obiba_main_app_angular,$(mica_version))
	$(call inject-version-info,themes/,obiba_bootstrap,$(mica_version))
	git commit -a -m "version updated to $(mica_current_tag)"

# inject-version-info-version function: remove (if present) and add specified version number to project info file
inject-version-info = cd drupal/$(1) && \
	sed -i "/^version/d" $2/$2.info && \
	sed -i "/^project/d" $2/$2.info && \
	sed -i "/^datestamp/d" $2/$2.info && \
	sed -i "/Information added by obiba.org packaging script/d" $2/$2.info && \
	echo "; Information added by obiba.org packaging script on $(release_date)" >> $2/$2.info && \
	echo "version = $(3)" >> $2/$2.info && \
	echo "project = $2" >> $2/$2.info && \
	echo "datestamp = $(datestamp)" >> $2/$2.info