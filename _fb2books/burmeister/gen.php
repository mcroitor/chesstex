<?php

$tpl = '<div class="chess-problem">
<div class="problem-title">№ {num}.</div>
<pre class="chess-diagram"><img src="./images/diagram{code}.png" /></pre>
<div class="problem-title">Мат в два хода.</div>
<div class="problem-title">Mat en deux coups.</div>
</div>';

$num = 1;

$result = "";

while($num <= 120) {
    $code = str_pad($num + 12, 3, "0", STR_PAD_LEFT);
    $result .= str_replace(['{num}', '{code}'], [$num, $code], $tpl) . PHP_EOL;
    ++ $num;
}

file_put_contents("out.html", $result);