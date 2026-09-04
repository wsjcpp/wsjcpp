
// fill code mirror
document.addEventListener("DOMContentLoaded", function(event) { 
    var elements = $('.cm-show-code');
    for (var i = 0; i < elements.length; i++) {
        var el = elements[i];
        var mode = $(el).attr('cm-mode');
        var cm_el = CodeMirror.fromTextArea(el, {
            lineNumbers: true,
            mode: mode,
            readOnly: true,
            // viewportMargin: 8
        });
        var height = cm_el.lineCount() * cm_el.defaultTextHeight() + 10;
        cm_el.setSize('100%', height);
    }
});

function switch_menu() {
    var el = document.getElementById('main_menu');
    if (el.style.display === '') {
        el.style.display = 'block';
    } else {
        el.style.display = '';
    }
}

function close_menu() {
    var el = document.getElementById('main_menu');
    el.style.display = '';
}

function open_main() {
    document.getElementById('content_main').style.display = 'block';
    document.getElementById('content_packages').style.display = 'none';
}


window.packages = []
function showFilteredPackages(filter) {
    var pkg_list = document.getElementById('packages_list');
    
    pkg_list.innerHTML = "";

    $('#all_packages').html(window.packages.length);
    filter = filter.toLowerCase();
    var found_packages = 0;

    for (var i in window.packages) {
        var pkg = window.packages[i];
        if (!pkg.name) continue;
        if (pkg.fulltextsearch.indexOf(filter) == -1) continue;
        var links = [];
        for (var t in pkg.links) {
            var lnk = pkg.links[t];
            links.push('<a href="' + lnk.url + '" target="_blank">' + lnk.title + "</a>");
        }
        found_packages++;
        pkg_list.innerHTML += 
            '<tr>'
            + '<td><hr><strong>' + pkg.name + '</strong><br>'
            + '' + pkg.description + '<br><br><div class="wsjcpp-hightlight-code">' + pkg.command + '</div><br>'
            + 'Links: ' + links.join(" | ") + '<br><br>'
            + '</td>'
            + '</tr>';
    }
    document.getElementById('found_packages').innerHTML = found_packages;
}

function open_packages() {
    document.getElementById('content_main').style.display = 'none';
    document.getElementById('content_packages').style.display = 'block';

    // scroll to top
    window.scrollTo( 0, 0 );
    document.getElementById('search_package').style.display = 'none';

    $.ajax({
        url: "./wsjcpp-packages.json"
    }).done(function(r) {
        for (var i in r) {
            var pkg = r[i];
            pkg.fulltextsearch = pkg.name + ' ' + pkg.description + ' ' + pkg.command + ' ';
            for (var t in pkg.links) {
                pkg.fulltextsearch += pkg.links[t].url + ' ' + pkg.links[t].title
            }
            pkg.fulltextsearch = pkg.fulltextsearch.toLowerCase()
            window.packages.push(pkg);
        }
        // window.packages = r;
        showFilteredPackages("");
        document.getElementById('search_package').value = "";
        document.getElementById('search_package').style.display = '';
    })
    
    document.getElementById('search_package').onkeyup = function(e) {
        console.log(e);
        showFilteredPackages($("#search_package").val())
    }
}

