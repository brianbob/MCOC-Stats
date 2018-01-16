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
            text: "AQ Points Over Time",
            verticalAlign: "top", 
            horizontalAlign: "left",
            padding: 15,
            margin: 30
          },
          axisY: {
            title: "Points",
            titleFontSize: 24,
          },
          axisX: {
            valueFormatString: "DD-MMM" ,
            labelAngle: -37
          },
          data: [{
            type: "line",
            xValueType: "dateTime",
            dataPoints: dps
          }]
        });
        chart.render();

      });
    }
  };
})(jQuery);