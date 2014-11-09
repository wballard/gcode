
//Vacuum table grid array, the idea is a large grid of air channels with
//shallower half channels an a nice central air-hole.

//This is in mm, at least in my head

table_backing=6;
table_thickness=20;
table_width=1140;
table_length=960;
channel_thickness=8;
grid_size=120;



//draw a single air_tile, this will inset the cut of the air
//channel insize the perimiter of the grid_size
module air_tile(start_x, start_y, start_z, grid_size, channel_depth) {
  translate([start_x, start_y, start_z]) {
    difference() {
      cube([grid_size, grid_size, channel_depth]);

      //perimieter air channels
      cube([grid_size, channel_thickness, channel_depth]);
      translate([0, grid_size-channel_thickness, 0])
        cube([grid_size, channel_thickness, channel_depth]);
      cube([channel_thickness, grid_size, channel_depth]);
      translate([grid_size-channel_thickness, 0, 0])
        cube([channel_thickness, grid_size, channel_depth]);

      //half channels
      translate([0, (grid_size-channel_thickness)/2, channel_depth/2])
        cube([grid_size, channel_thickness, channel_depth]);
      translate([(grid_size-channel_thickness)/2, 0, channel_depth/2])
        cube([channel_thickness, grid_size, channel_depth]);
    }
  }
}

//this is the tabletop board
cube([table_width, table_length, table_backing]);

//now loop and render the air channel 'tiles'
channel_depth = table_thickness - table_backing;
for (x = [0 : grid_size-channel_thickness: table_width]) {
  for (y = [0 : grid_size-channel_thickness: table_length]) {
    if (x+grid_size < table_width && y+grid_size < table_length) {
      air_tile(x, y, table_backing, grid_size, channel_depth);
    }
  }
}
