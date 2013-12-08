	$(function () {
		$("#alert").hide();
	
    $(document).ready(function() {
        Highcharts.setOptions({
            global: {
                useUTC: false
            }
        });
    
        var chart;
        $('#graphTemp').highcharts({
            chart: {
                type: 'spline',
                animation: Highcharts.svg, // don't animate in old IE
                marginRight: 10,
                events: {
                    load: function() {
                        // set up the updating of the chart each second
                        var series = this.series[0];
                        setInterval(function() {
                            $.ajax({
								async: false,
								url: "/Hackwaw/FluAlert/Backend/public/site/sensor?type=T",
								type: "GET",
								success: function (msg) 
								{
									 var x = (new Date()).getTime(), // current time
									 y = FormatNumberLength(msg.value,2);
									 series.addPoint([x, y], true, true);
									 $("#graphTempValue").text(y);
								}
								});
							
							
                        }, 1000);
                    }
                }
            },
            title: {
                text: ''
            },
            xAxis: {
                type: 'datetime',
                tickPixelInterval: 150
            },
            yAxis: {
                title: {
                    text: 'Temp'
                },
                plotLines: [{
                    value: 0,
                    width: 1,
                    color: '#c0392b'
                }]
            },
            tooltip: {
                formatter: function() {
                        return '<b>'+ this.series.name +'</b><br/>'+
                        Highcharts.dateFormat('%Y-%m-%d %H:%M:%S', this.x) +'<br/>'+
                        Highcharts.numberFormat(this.y, 2);
                }
            },
            legend: {
                enabled: false
            },
            exporting: {
                enabled: false
            },
            series: [{
                name: 'Temp',
				color: '#c0392b',
                data: (function() {
                    // generate an array of random data
                    var data = [],
                        time = (new Date()).getTime(),
                        i;
    
                    for (i = -19; i <= 0; i++) {
                        data.push({
                            x: time + i * 1000,
                            y: 36 + Math.random()
                        });
                    }
                    return data;
                })()
            }]
        });
    });
    
});

	$(function () {
    $(document).ready(function() {
        Highcharts.setOptions({
            global: {
                useUTC: false
            }
        });
    
        var chart;
        $('#graphHeartrate').highcharts({
            chart: {
                type: 'spline',
                animation: Highcharts.svg, // don't animate in old IE
                marginRight: 10,
                events: {
                    load: function() {
                        // set up the updating of the chart each second
                        var series = this.series[0];
                        setInterval(function() {
							$.ajax({
								async: false,
								url: "/Hackwaw/FluAlert/Backend/public/site/sensor?type=H",
								type: "GET",
								dataType: "json",
								contentType: "text/plain; charset=utf-8",
								success: function (msg) 
								{
									 var x = (new Date()).getTime(), // current time
									 y = FormatNumberLength(msg.value,2);
									 series.addPoint([x, y], true, true);
									 $("#graphHeartrateValue").text(y);
								}
								});
                        }, 1000);
                    }
                }
            },
            title: {
                text: ''
            },
            xAxis: {
                type: 'datetime',
                tickPixelInterval: 150
            },
            yAxis: {
                title: {
                    text: 'HeartRate'
                },
                plotLines: [{
                    value: 0,
                    width: 1,
                    color: '#d35400'
                }]
            },
            tooltip: {
                formatter: function() {
                        return '<b>'+ this.series.name +'</b><br/>'+
                        Highcharts.dateFormat('%Y-%m-%d %H:%M:%S', this.x) +'<br/>'+
                        Highcharts.numberFormat(this.y, 2);
                }
            },
            legend: {
                enabled: false
            },
            exporting: {
                enabled: false
            },
            series: [{
                name: 'HeartRate',
				color: '#d35400',
                data: (function() {
                    // generate an array of random data
                    var data = [],
                        time = (new Date()).getTime(),
                        i;
    
                    for (i = -19; i <= 0; i++) {
                        data.push({
                            x: time + i * 1000,
                            y: 88 + Math.random()
                        });
                    }
                    return data;
                })()
            }]
        });
    });
    
});
function checkAlert() {
	var heart = parseInt($("#graphTempValue").text());
	var temp = parseInt($("#graphTempValue").text());
	
	if(temp > 30 && heart > 100) {
		$("#alert").show();
	}
}
function FormatNumberLength(num, length) {
    return parseInt(num).toPrecision(3);
}