<!--
  ~ Copyright (c) 2015 OBiBa. All rights reserved.
  ~
  ~ This program and the accompanying materials
  ~ are made available under the terms of the GNU Public License v3.0.
  ~
  ~ You should have received a copy of the GNU General Public License
  ~ along with this program.  If not, see <http://www.gnu.org/licenses/>.
  -->

<div ng-app="DataAccessRequest">
  <?php print l('<i class="fa fa-plus"></i> ' . t('New Data Access Request'), 'mica/data-access/request', array(
      'html' => TRUE,
      'fragment' => '/new',
      'attributes' => array('class' => array('btn', 'btn-info'))
    )
  ); ?>

  <table class="table table-striped" id="table-requests"></table>

  <div class="modal fade" id="delete-modal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel"
    aria-hidden="true">
    <div class="modal-dialog">
      <div class="modal-content">
        <div class="modal-header">
          <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span
              aria-hidden="true">&times;</span></button>
          <h4 class="modal-title" id="myModalLabel"><i
              class="fa fa-exclamation-triangle"></i><?php print t('Delete Data Access Request'); ?>
          </h4>
        </div>
        <div class="modal-body">
          <p><?php print t('Are you sure you want to delete Data Access :'); ?>'<span
              id="data-access-title"></span>' <?php print t('requested by :'); ?>
            <span id="data-access-applicant"></span> ?
          </p>
        </div>
        <div class="modal-footer">
          <button type="button" class="btn btn-default" data-dismiss="modal"><?php print t('Cancel'); ?>
          </button>
          <button id="clickedDelete" type="button" class="btn btn-primary"
            data-delete-resource=""><?php print t('Delete'); ?>
          </button>
        </div>
      </div>
    </div>
  </div>


</div>
