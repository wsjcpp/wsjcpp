function wsjcppHighlightYamlRules() {
    return [{
        "re": /^(.*)(".*")(.*)$/,
        "replace": '$1<whc class="string">$2</whc>$3'
    },{
        "re": /^([ ]*)([\-]{0,1}[ ]+[a-z\\-]+)(:.*)$/,
        "replace": '$1<whc class="blue">$2</whc>$3'
    },{
        "re": /^([ ]*)([a-z\\-_]+)(:.*)$/,
        "replace": '$1<whc class="blue">$2</whc>$3'
    },{
        "re": /^(.*)(# .*)$/,
        "replace": '$1<whc class="green">$2</whc>'
    }]
}

function wsjcppHighlightDockerfileRules() {
    return [{
        "re": /^(RUN|FROM)(.*)$/,
        "replace": '<whc class="blue">$1</whc>$2'
    },{
        "re": /^(.*)(# .*)$/,
        "replace": '$1<whc class="green">$2</whc>'
    }]
}

function wsjcppHighlightShellZshRules() {
    return [{
        "re": /^(% )([a-z]+[ ]+)(.*)$/,
        "replace": '$1<whc class="blue">$2</whc>$3'
    },{
        "re": /^(.*)(https:\/\/[a-z.\/]+)(.*)$/,
        "replace": '$1<whc class="string">$2</whc>$3'
    },{
        "re": /^(% )(.*)$/,
        "replace": '<whc class="blue">$1</whc>$2'
    }]
}

function wsjcppHighlightShellBashRules() {
    return [{
        "re": /^(\$ )([a-z]+[ ]+)(.*)$/,
        "replace": '$1<whc class="blue">$2</whc>$3'
    },{
        "re": /^(.*)(https:\/\/[a-z.\-:\/]+)(.*)$/,
        "replace": '$1<whc class="string">$2</whc>$3'
    },{
        "re": /^(\$ )(.*)$/,
        "replace": '<whc class="blue">$1</whc>$2'
    }]
}

function wsjcppHighlightClikeRules() {
    return [{
        "re": /^(.*)(".*")(.*)$/,
        "replace": '$1<whc class="string">$2</whc>$3'
    },{
        "re": /^(#include)(.*)$/,
        "replace": '<whc class="blue">$1</whc>$2'
    },{
        "re": /^(.*)([ ]+if[ ]+|[ ]+return[ ]+)(.*)$/,
        "replace": '$1<whc class="blue">$2</whc>$3'
    },{
        "re": /^(int )(.*)$/,
        "replace": '<whc class="blue">$1</whc>$2'
    },{
        "re": /^(.* )(\/\/.*)$/,
        "replace": '$1<whc class="green">$2</whc>'
    }]
}

function doWsjcppHighlight(el) {
    if (el.attributes['hightlighted']) {
        return;
    }
    el.innerHTML = el.innerHTML.trim();
    var lines = el.innerHTML.split("\n");
    var rules = []
    if (el.classList.contains("shell-zsh")) {
        rules = wsjcppHighlightShellZshRules()
    } else if (el.classList.contains("yaml")) {
        rules = wsjcppHighlightYamlRules();
    } else if (el.classList.contains("text")) {
        // no hightlights
    } else if (el.classList.contains("shell-bash")) {
        rules = wsjcppHighlightShellBashRules();
    } else if (el.classList.contains("dockerfile")) {
        rules = wsjcppHighlightDockerfileRules();
    } else if (el.classList.contains("clike")) {
        rules = wsjcppHighlightClikeRules();
    } else {
        console.warn("Unknown hightlight mode for ", el);
    }
    var new_lines = []
    if (rules.length > 0) {
        
        for (var i = 0; i < lines.length; i++) {
            var line = lines[i];
            for (var h = 0; h < rules.length; h++) {
                var rule = rules[h];
                let result = line.match(rule.re);
                if (result) {
                    line = line.replace(rule.re, rule.replace)
                }
            }
            new_lines.push(line);
        }
        el.innerHTML = new_lines.join("\n").trim();
    }
    el.setAttribute('hightlighted', 'yes');
}

function doWsjcppHighlightsAll() {
    var els = document.getElementsByClassName("wsjcpp-hightlight-code");
    for (var i = 0; i < els.length; i++) {
        doWsjcppHighlight(els[i]);
    }
}

document.addEventListener("DOMContentLoaded", function(event) { 
    doWsjcppHighlightsAll()
});