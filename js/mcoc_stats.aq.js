(function($){
  Drupal.behaviors.mymodule = {
    attach: function(context, settings) {
      $(document).ready(function() {

        var dps = Drupal.settings.mcoc_stats.data;
        //alert(dps);
            
        var chart = new CanvasJS.Chart("pointChartContainer", {
          animationEnabled: true,
          theme: "light2",
          zoomEnabled: true,
          title: {
            text: "BG2's AQ Total Point Trend"
          },
          axisY: {
            title: "Points",
            titleFontSize: 24,
          },
          axisX: {
            title: "Time",
            titleFontSize: 24,
          },
          data: [{
            type: "line",
            xValueType: "dateTime",
            yValueFormatString: "#,##0",
            dataPoints: dps
          }]
        });
        chart.render();

      });
    }
  };
})(jQuery);