<?php

$problems = new DOMDocument();
$problems->loadHTMLFile("p002.xhtml");
$pbm_path = new DOMXPath($problems);

$pbm = $pbm_path->query("//div[@class='chess-problem']");
echo "problems found = " . count($pbm) . PHP_EOL;

$solutions = new DOMDocument();
$solutions->loadHTMLFile("p003.xhtml");
$sol_path = new DOMXPath($solutions);
$sol = $sol_path->query("//p[@class='solution']");

echo "solutions found = " . count($sol) . PHP_EOL;

$result = new DOMDocument("1.0", "UTF-8");

$root = $result->createElement("body");

for($i = 0; $i < count($pbm); ++$i) {
    echo $pbm->item($i)->nodeValue . PHP_EOL;
    $root->appendChild($result->importNode($pbm->item($i), true));
    $root->appendChild($result->importNode($sol->item($i), true));
}

$result->appendChild($root);

$result->save("oops.xhtml");