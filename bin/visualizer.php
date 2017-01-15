#!/usr/bin/php
<?php
/*
 * Copyright 2015 Marco Zanella
 * This file is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Victor.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * Returns array of nodes from an instance file.
 * @param string filename Path to instance file
 * @return array Array of nodes
 */
function readNodes($filename) {
    $fh = fopen($filename, "r");
    $nodes = [];

    list($size, $map_size, $min_id, $max_id) = fscanf($fh, "%d %d %d %d");

    for ($i = 0; $i < $size; $i++) {
        list($id, $x, $y) = fscanf($fh, "%d %f %f");
        $nodes[$id] = ['x' => $x, 'y' => $y];
    }

    fclose($fh);

    return $nodes;
}


/**
 * Finds maximum item in array of nodes.
 * @param string key Key to maximise
 * @return float Maximum item
 */
function findMax($nodes, $key) {
    $max = 0.0;

    foreach ($nodes as $node) {
        $max > $node[$key] or $max = $node[$key];
    }

    return $max;
}


/**
 * Returns list of identifiers of node.
 * @param string filename Path to solution file
 * @return array Array of identifiers of nodes
 */
function readSolution($filename) {
    $fh = fopen($filename, "r");

    list($size, $cost) = fscanf($fh, "%d %f");

    $solution = [];
    for ($i = 0; $i < $size; $i++) {
        list($id, $x, $y) = fscanf($fh, "%d %f %f");
        $solution[] = $id;
    }

    fclose($fh);

    return $solution;
}


/**
 * Creates a wrapper for an image object.
 * @param int   x      Width of the image
 * @param int   y      Height of the image
 * @param float scale  Scale of the image
 * @param int   border Size of borders of image
 * @return mixed Image
 */
function createImage($x, $y, $scale, $border) {
    $image = [
        'size_x' => $border + $x * $scale + $border,
        'size_y' => $border + $y * $scale + $border,
        'scale'  => $scale,
        'border' => $border
    ];

    $imgObj = imagecreatetruecolor($image['size_x'], $image['size_y']);
    $colors = [
        'background' => imagecolorallocate($imgObj, 220, 235, 255),
        'fill'       => imagecolorallocate($imgObj,  80, 135, 180),
        'border'     => imagecolorallocate($imgObj,  40,  65, 090)
    ];

    $image['object'] = $imgObj;
    $image['colors'] = $colors;

    imagefill($imgObj, 0, 0, $colors['background']);
    imagesetthickness($imgObj, 2);

    return $image;
}


/**
 * Draws a node.
 * @param mixed image Image
 * @param mixed node  Node
 */
function drawNode($image, $node) {
    $x = $node['x'] * $image['scale'] + $image['border'];
    $y = $node['y'] * $image['scale'] + $image['border'];

    imagefilledellipse($image['object'], $x, $y, 10, 10, $image['colors']['border']);
    imagefilledellipse($image['object'], $x, $y,  7,  7, $image['colors']['fill']);
}


/**
 * Draws a line.
 * @param mixed image Image
 * @param mixed from  Starting node
 * @param mixed to    Ending node
 */
function drawLine($image, $from, $to) {
    $scale  = $image['scale'];
    $border = $image['border'];
    $x1 = $from['x'] * $scale + $border;
    $y1 = $from['y'] * $scale + $border;
    $x2 = $to['x']   * $scale + $border;
    $y2 = $to['y']   * $scale + $border;

    imageline($image['object'], $x1, $y1, $x2, $y2, $image['colors']['border']);
}


/**
 * Deletes an image wrapper.
 * @param mixed image Image to delete
 */
function deleteImage($image) {
    foreach ($image['colors'] as $color) {
        imagecolordeallocate($image['object'], $color);
    }
    imagedestroy($image['object']);
}




/***********************************************************************
 * Entry point of the script
 **********************************************************************/
// Sanity check
count($argv) >= 3 or die(
    "Usage: $argv[0] <instance_file> <solution_file> " .
    "[<output_file = out.png> [<scale = 1000>]]\n"
);
isset($argv[3]) or $argv[3] = "out.png";
isset($argv[4]) or $argv[4] = 1000;


// Initialization
$nodes    = readNodes($argv[1]);
$solution = readSolution($argv[2]);
$image    = createImage(findMax($nodes, 'x'), findMax($nodes, 'y'), $argv[4], 25);


// Draws instance
foreach ($nodes as $node) {
    drawNode($image, $node);
}


// Draws the solution
for ($i = 0; $i < count($solution); $i++) {
    $current = $nodes[$solution[$i]];
    $next    = $nodes[$solution[($i + 1) % count($solution)]];
    drawLine($image, $current, $next);
}


// Saves image
imagepng($image['object'], $argv[3]);


// Memory free
deleteImage($image);
?>
