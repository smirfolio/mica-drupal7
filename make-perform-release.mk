#
#Seed versions of current release
#
#
include make-seed-versions.mk

#
#
#Push to GitHub
#
#
git-mica-release: inject-version-info github-release

#
# Push to Drupal.org
#
git-push-mica:
	$(call clear-version-info,drupal/modules,obiba_mica) && \
	$(call clear-version-info,drupal/modules/obiba_mica,obiba_mica_study) && \
	$(call clear-version-info,drupal/modules/obiba_mica,obiba_mica_commons) && \
	$(call clear-version-info,drupal/modules/obiba_mica,obiba_mica_network) && \
	$(call clear-version-info,drupal/modules/obiba_mica,obiba_mica_model) && \
	$(call git-prepare,$(drupal_org_mica),obiba_mica,$(mica_branch)) . && \
	cp -r drupal/modules/obiba_mica/* target/drupal.org/obiba_mica && \
	$(call git-finish,obiba_mica,$(mica_branch))

clear-version-info = sed -i "/^version/d" $(1)/$2/$2.info && \
	sed -i "/^project/d" $(1)/$2/$2.info && \
	sed -i "/^datestamp/d" $(1)/$2/$2.info && \
	sed -i "/Information added by obiba.org packaging script/d" $(1)/$2/$2.info

github-release = echo "Enter a message for this tag push release?" && \
	read git_push_msg && \
	git tag -a $(mica_current_tag) -m "$$git_push_msg" && \
	git push upstream/$(mica_current_tag) && \