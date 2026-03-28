# Clases IoT con Slidev

Presentaciones del curso construidas con [Slidev](https://github.com/slidevjs/slidev).

## Desarrollo local

```bash
npm install
npm run dev
```

Luego abre `http://localhost:3030`.

## Abrir otro archivo `.md`

`npm run dev` abre el archivo por defecto, que es `slides.md`.

Si quieres levantar otra presentación, puedes usar una forma más corta con `npx`:

```bash
npx slidev clase_3.md --open
```

También funciona con cualquier otro archivo, por ejemplo:

```bash
npx slidev clase_1.md --open
```

Alternativa equivalente con `npm`:

```bash
npm exec slidev clase_3.md -- --open
```

## Build local

```bash
npm run build
```

## Deploy automático con GitHub Pages

El repositorio ya queda configurado para publicar las slides con GitHub Actions en cada push a `main`.

URL esperada:

`https://pepeedwards.github.io/clases-iot/`

Pasos necesarios en GitHub:

1. Entra a `Settings > Pages`.
2. En `Source`, selecciona `GitHub Actions`.
3. Haz push a `main`.
4. Espera que termine el workflow `Deploy Slides to GitHub Pages`.

El workflow compila Slidev hacia `dist`, publica ese directorio en GitHub Pages y además genera `404.html` para que las rutas del sitio funcionen mejor en Pages.
