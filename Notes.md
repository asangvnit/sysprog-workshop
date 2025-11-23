## Rendering markdown files locally

[grip][grip] package provides ability to render [GFM][gfm] (GitHub Flavored
Markdown) files locally. You can install it with:

```
$ pip install grip
```

To run int you can use:

```console
asangdani@sysprog-workshop % grip . 0.0.0.0
 * Serving Flask app 'grip.app'
 * Debug mode: off
WARNING: This is a development server. Do not use it in a production deployment.
Use a production WSGI server instead.
 * Running on all addresses (0.0.0.0)
 * Running on http://127.0.0.1:6419
 * Running on http://192.168.88.2:6419
Press CTRL+C to quit
```

As of this writing, it doesn't render embedded mermaid digrams correctly.

[grip]: https://github.com/joeyespo/grip
[gfm]: https://github.github.com/gfm/
