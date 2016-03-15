<?php
/**
 * @file
 * Obiba Mica Module.
 *
 * Copyright (c) 2016 OBiBa. All rights reserved.
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
?>

<li class="facets"
  data-form-id="facet-search-<?php print $aggregation_facet ?>">
  <table>
    <tr>
      <td>
        <?php
        if ($term->key === "0" || !empty($term->key)) {
          if (!empty($term->title)) {
            $title = t($term->title);
          }
          else {
            $title = $term->key;
          }
        }
        $tooltip = empty($term->description) ? (strlen($title) < 30 ? '' : $title) : $term->description;
        ?>
        <span id="checkthebox"
          class="term-field <?php print $type_string . $aggregation_facet; ?> unchecked"
          aggregation="<?php print $type_string . $aggregation_facet . '[]'; ?>"
          value="<?php print  htmlspecialchars($title); ?>"
          data-value="<?php print  $term->key; ?>"
          data-toggle="tooltip"
          title="<?php print htmlspecialchars($tooltip) ?>">
          <i class="glyphicon glyphicon-unchecked"></i>
          <div class="tilte-term"><?php print $title ?></div>
        </span>
      </td>
      <?php if ($query_request && ($_SESSION['request-search-response'] == 'no-empty') && $term->count != 0) : ?>
        <td class='term-count'>
          <span data-toggle="tooltip" data-placement="top" title="Filtered">
            <?php print obiba_mica_commons_format_number($term->count); ?>
          </span>
        </td>
      <?php endif; ?>
      <?php if (!$query_request): ?>
        <td class='term-count'>
          <span data-toggle="tooltip" data-placement="top"
            title="All"><?php print obiba_mica_commons_format_number($term->default); ?></span>
        </td>
      <?php elseif (($term->count != $term->default) || ($_SESSION['request-search-response'] == 'empty')) : ?>
        <td class='term-default'>
          <span data-toggle="tooltip" data-placement="top" title="All">
            <?php print obiba_mica_commons_format_number($term->default); ?>
          </span>
        </td>
      <?php endif; ?>
    </tr>
  </table>
</li>
<input
  id="<?php print $type_string . $aggregation_facet . '[]-' . $term->key; ?>"
  name="<?php print $type_string . 'terms:' . $aggregation_facet . '[]'; ?>"
  type="hidden" value="">
