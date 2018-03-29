/*
 * Copyright (c) 2018 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file
 * code to initialise Timeline
 */

(function ($) {
  var dceModalInfo;
  Drupal.behaviors.dce_detail_modal = {
    attach: function (context, settings) {
      dceModalInfo = settings.dceModalInfoArray;

      if (dceModalInfo) {
        $('#dce-modal').on('show.bs.modal', function (event) {
          var link = $(event.relatedTarget);
          var modal = $(this);
          seedModal(modal, link.data('dceid'));
        });
        $('#dce-modal').on('hide.bs.modal', function () {
          var modal = $(this);
          destroyModal(modal);
        });
      }

      function seedModal(popup, dceId) {
        return Drupal.behaviors.dce_detail_modal.seedmodal(popup, dceId);
      }

      function destroyModal(modal) {
        return Drupal.behaviors.dce_detail_modal.destroyModal(modal);
      }
    }
  };

  function getDceFromId(dceId) {
    var dce;
    for (var key in dceModalInfo) {
      dce = dceModalInfo[key].find(function (dce) {
        return dce.dce_uid === dceId;
      });
      if (dce) {
        return dce;
      }
    }
  }

  Drupal.behaviors.dce_detail_modal.destroyModal = function (popup) {
    popup.find('.dce-file-browser').hide();
    var fileBrowser = $(popup.find('.files-documents'));
    fileBrowser[0].firstElementChild.setAttribute('doc-path', '/');
    fileBrowser[0].firstElementChild.setAttribute('doc-id', '');
    fileBrowser[0].firstElementChild.setAttribute('token-key', '');
    fileBrowser[0].firstElementChild.setAttribute('refresh', false);
    fileBrowser[0].firstElementChild.classList.add('hide');
  };

  Drupal.behaviors.dce_detail_modal.seedmodal = function (popup, dceId) {
    var dce = getDceFromId(dceId);
    var popup = $(popup[0]);
    if (dce) {
      popup.find('.dce-modal-title').text(dce['dce'].name);

      if (dce['dce'].description) {
        popup.find('.modal-dce-description').html(dce['dce'].description);
      }
      else {
        popup.find('.modal-dce-description').empty();
      }

      if (dce['dce'].startYear) {
        popup.find('.start-year-title').text(dce['dce'].startYear.title);
        popup.find('.start-year').html(dce['dce'].startYear.value);
      }
      else {
        popup.find('.dce-start-year').empty();
      }

      if (dce['dce'].endYear) {
        popup.find('.end-year-title').text(dce['dce'].endYear.title);
        popup.find('.end-year').html(dce['dce'].endYear.value);
      }
      else {
        popup.find('.dce-end-year').empty();
      }

      if (dce['dce'].dataSources) {
        popup.find('.data-sources-title').text(dce['dce'].dataSources.title);
        popup.find('.data-sources-list').html(dce['dce'].dataSources.list);
      }
      else {
        popup.find('.dce-data-sources').empty();
      }

      if (dce['dce'].administrativeDatabases) {
        popup.find('.admin-databases-title').text(dce['dce'].administrativeDatabases.title);
        popup.find('.admin-databases-list').html(dce['dce'].administrativeDatabases.list);
      }
      else {
        popup.find('.dce-admin-databases').empty();
      }

      if (dce['dce'].bioSamples) {
        popup.find('.bio-samples-title').text(dce['dce'].bioSamples.title);
        popup.find('.bio-samples-list').html(dce['dce'].bioSamples.list);
      }
      else {
        popup.find('.dce-bio-samples').empty();
      }

      if (dce['dce'].bioSamples) {
        popup.find('.bio-samples-title').text(dce['dce'].bioSamples.title);
        popup.find('.bio-samples-list').html(dce['dce'].bioSamples.list);
      }
      else {
        popup.find('.dce-bio-samples').empty();
      }

      if (dce.file_browser) {
        popup.find('.dce-file-browser').show();
        var fileBrowser = $(popup.find('.files-documents'));
        fileBrowser[0].firstElementChild.classList.add('show');
        fileBrowser[0].firstElementChild.setAttribute('doc-path', dce.file_browser.marckup['doc_path']);
        fileBrowser[0].firstElementChild.setAttribute('doc-id', dce.file_browser.marckup['doc_id']);
        fileBrowser[0].firstElementChild.setAttribute('token-key', dce.file_browser.marckup['token_key']);
        fileBrowser[0].firstElementChild.setAttribute('refresh', true);
        fileBrowser[0].firstElementChild.setAttribute('show-title', true);
      }
      else {
        popup.find('.dce-file-browser').hide();
      }
    }
  }

})(jQuery);