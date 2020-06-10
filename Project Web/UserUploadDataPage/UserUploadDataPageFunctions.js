async function JSONParser(file) 
{
    let text = await file.text();
    let JSONObject = JSON.parse(text);
    MapSetter("mapid", JSONObject)
}

function MapSetter(MapId, JSONObject)
{
    let CenterCoordinates = [38.230462, 21.753150];
    var map = L.map(MapId, { drawControl: true }).setView(CenterCoordinates, 14);
    L.tileLayer("https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png",{
        attribution: 'Map data &copy; <a href="https://www.openstreetmap.org/">OpenStreetMap</a> contributors'
    }).addTo(map);

    var drawnItems = new L.FeatureGroup();
    map.addLayer(drawnItems);

    drawControl = new L.Control.Draw({
        draw : {
            position : 'topright',
            polyline : false,
            rectangle : false,
            circle : false,
            polygon: false,
            marker: false
        },
        edit : {
            featureGroup: drawnItems
          }
    });
    map.addControl(drawControl);

    // map.on(L.Draw.Event.CREATED, function (e) {
    //     var layer = e.layer;
    //      drawnItems.addLayer(layer);
    //  });
    
    let MarkersList = [];
    // let FullJSONObject = JSON.parse(JSON.stringify(JSONObject));
    // let FullMarkersList = [];
    // for(i = 0; i < FullJSONObject.locations.length; i++)
    // {
    //     coordinates = [ FullJSONObject.locations[i].latitudeE7/10000000, FullJSONObject.locations[0].longitudeE7/10000000]
    //     marker = L.marker(coordinates).addTo(map);
    //     MarkersList.push(marker);
    //     marker.bindPopup(coordinates.toString()).openPopup();
    // }

    // var circle = L.circle(CenterCoordinates, {
    //     color: 'red',
    //     fillColor: '#f03',
    //     fillOpacity: 0.5,
    //     radius: 10000
    // }).addTo(map);
    marker = L.marker(CenterCoordinates).addTo(map);
    let str = "Patras Center: ".concat(CenterCoordinates.toString());
    marker.bindPopup(str).openPopup();
    for(i = 0; i < JSONObject.locations.length; i++)
    {
        let coordinates = [ JSONObject.locations[i].latitudeE7/10000000, JSONObject.locations[i].longitudeE7/10000000]
        let distance = Math.sqrt( Math.pow((CenterCoordinates[0] - coordinates[0]), 2) + Math.pow((CenterCoordinates[1] - coordinates[1]), 2) );
        if (distance <= 0.1)
        {
            marker = L.marker(coordinates).addTo(map);
            marker.bindPopup(coordinates.toString()).openPopup();
            MarkersList.push(marker);
        }
    }

    // AJAX CALL
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "test.php",true);
    xhr.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
    xhr.onreadystatechange = function save() 
    {
        if (this.readyState == 4 && this.status == 200) 
        {
            var res = JSON.parse(this.response);
            if (res.status) {
              // OK - DO SOMETHING
              alert(res.message);
            } else {
              // ERROR - DO SOMETHING
              alert(res.message);
            }
        }
    };
    xhr.send(JSON.stringify(JSONObject));


    //Second try
    // var values = JSON.stringify(JSONObject);

    // jQuery.ajax({
    //     url: "test.php",
    //     type: "get",
    //     data: values ,
    //     success: function (response) 
    //     {
    //         console.log(response.headers);
    //         // You will get response from your PHP page (what you echo or print)
    //     },
    //     error: function(jqXHR, textStatus, errorThrown) {
    //         console.log(textStatus, errorThrown);
    //     }
    // });
}