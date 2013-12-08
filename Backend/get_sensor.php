<?php 

$file = 'data.txt';

$current = file_get_contents( $file );

$string = $_REQUEST[ 'data' ];
$string = str_replace( "\n", "", $string );
$string = str_replace( "\r", "", $string );

$current .= $string . "\n";

echo $string;

file_put_contents( $file, $current );

echo 'ok';