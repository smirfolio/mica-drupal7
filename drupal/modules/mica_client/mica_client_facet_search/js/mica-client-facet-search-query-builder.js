(function ($) {

  "use strict";



  /**
   * Constructor
   * @constructor
   */
  $.QueryViewRenderer = function () {
    this.container = $("<div></div>");
  };

  /**
   * Create a QueryViewRenderer
   * @type {{render: render}}
   */
  $.QueryViewRenderer.prototype = {

    render: function (jsonQuery) {
      this.jsonQuery = jsonQuery;
      var self = this;

      function updateWindowLocation(query) {
        window.location.search = window.location.search.replace(/([&]*query=)[^&]*([&]*)/g, query);
      }

      function createAgg(type, typeValues, aggType, name) {
        return $("<span type='button' class='badge'></span>").text(name + "is") //
          .on("click", function() {
            console.log("type", type);
            console.log("typeValues", typeValues);
            console.log("aggType", aggType);
            console.log(JSON.stringify(self.jsonQuery));
            delete typeValues[aggType][name];
            console.log("EMPTY", $.isEmptyObject(typeValues[aggType]));
            console.log(JSON.stringify(self.jsonQuery));
//            window.location.search = window.location.search.replace(/[&]*query=[^&]*/g, '');
          });
      }

      function createValue(value) {
        return $("<span type='button' class='badge'></span>").text(value) //
          .on("click", function() {
//            window.location.search = window.location.search.replace(/[&]*query=[^&]*/g, '');
          });
      }

      function createRefresh() {
        return $("<button type='button'><i class='glyphicon glyphicon-refresh'></i></button>") //
          .on("click", function() {
            updateWindowLocation('');
//            window.location.search = window.location.search.replace(/([&]*query=)[^&]*([&]*)/g, '');
          });
      }


      this.container.append(createRefresh());
      $.each(jsonQuery, function(type, typeValues) {
        $.each(typeValues, function(aggType, aggs) {
          $.each(aggs, function (name, values) {
            if (values.length > 0) {

              var aggContainer = createAgg(type, typeValues, aggType, name);
              self.container.append(aggContainer);
              $.each(values, function (i, value) {
                console.log(value);
                self.container.append(createValue(value));
              });
            }
          })
        });
      });

      return this.container;
    }
  };

}(jQuery));


(function ($) {

  /**
   * Helper used to extract query json from URL
   * @returns {*}
   */
  function getQueryParameter() {
    return (window.location.search.replace(/(^\?)/, '').split("&").map(function (n) {
      return n = n.split("="), this[n[0]] = n[1], this
    }.bind({}))[0])['query'];
  }

  Drupal.behaviors.query_builder = {
    attach: function (context, settings) {
      console.log("START");
      var qParam = getQueryParameter();
      if ($.isEmptyObject(qParam)) return;
      var view = new $.QueryViewRenderer().render(JSON.parse(decodeURIComponent(qParam)));
      $('#search-query').append(view);
    }
  }
})(jQuery);

