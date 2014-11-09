
//Vacuum table grid array, the idea is a large grid of air channels with
//shallower half channels an a nice central air-hole.

//This is in mm, at least in my head

table_backing=6;
table_thickness=20;
table_width=1140;
table_length=960;
channel_thickness=8;
grid_size=120;
grid_center_x=ceil(table_width/grid_size/2)*grid_size + channel_thickness/2;
grid_center_y=ceil(table_length/grid_size/2)*grid_size + channel_thickness/2;
echo(grid_center_x);
echo(grid_center_y);

difference() {
  //this is the tabletop board
  cube([table_width, table_length, table_thickness]);
  //cut away the air channels along the X
  for (x = [0 : grid_size: table_width]) {
    //major
    translate([x, 0, table_backing])
      cube([channel_thickness, table_length, table_thickness]);
    //minor
    translate([x + (grid_size-channel_thickness)/2, 0, table_backing*2])
      cube([channel_thickness, table_length, table_thickness]);
  }
  //cut away the air channels along the Y
  for (y = [0 : grid_size: table_length]) {
    //major
    translate([0, y, table_backing])
      cube([table_width, channel_thickness, table_thickness]);
    translate([0, y + (grid_size-channel_thickness)/2, table_backing*2])
      cube([table_width, channel_thickness, table_thickness]);
  }
  //central air hole
  translate([grid_center_x, grid_center_y, 0])
    cylinder(table_thickness*2, 30, true);
}
