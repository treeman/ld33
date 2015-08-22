#include "engine/locator.hxx"
#include "monster.hxx"
#include "bullet.hxx"
#include "world.hxx"

const float move_speed = 300;
const int width = 332;
const int height = 305;

Monster::Monster(World &world) : world(world) {
    spr = create_sprite("monster_main.png");
}

void Monster::handle_input(const sf::Event &e) {
    switch (e.type) {
        case sf::Event::KeyPressed:
            if (e.key.code == sf::Keyboard::H) fire_left();
            if (e.key.code == sf::Keyboard::L) fire_right();
            break;
        default:
            break;
    }
}

void Monster::set_pos(FPoint _pos) {
    pos = _pos;
    // TODO better hitbox
    if (pos.x < 0) pos.x = 0;
    if (pos.x + width > 800) pos.x = 800 - width;
    if (pos.y < 0) pos.y = 0;
    if (pos.y + height > 500) pos.y = 500 - height;

    D_.tmp(fmt("monster pos: %f, %f", pos.x, pos.y));
    spr.setPosition(pos);
}

void Monster::move(FPoint dv) {
    pos = pos + dv;
    set_pos(pos);
    for (auto s : spawners) {
        s->move(dv);
    }
}

void Monster::update(const sf::Time &dt) {
    move_dir = IPoint();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) move_dir.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) move_dir.x += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) move_dir.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) move_dir.y += 1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) fire_eyes();

    FPoint dv = FPoint(move_dir).normalize() * move_speed * dt.asSeconds();
    move(dv);
}

void Monster::draw(sf::RenderWindow &w) {
    w.draw(spr);
}

void Monster::fire_bullets(vector<Bullet*> bullets) {
    for (auto x = bullets.begin(); x != bullets.end(); ++x) {
        shared_ptr<Bullet> b(*x);
        b->pos = b->pos + pos;
        world.add_bullet(b);
    }
}

void Monster::fire_eyes() {
    if (eyes_fire_delay.getElapsedTime().asSeconds() > 0.05) {
        string path = "cbullet.png";
        vector<Bullet*> bullets = {
            new VelBullet(path, 500, FPoint(1, 4), FPoint(115, 165)),
            new VelBullet(path, 500, FPoint(1, 2), FPoint(185, 148)),
        };
        fire_bullets(bullets);

        // Offset for monster position
        eyes_fire_delay.restart();
    }
}

void Monster::fire_left() {
    L_("IMBA PEW!\n");
    shared_ptr<Bulletspawner> spawner(new Bulletspawner(world));
    spawner->set_pos(FPoint(85, 240) + pos);
    const int num = 80;
    for (int i = 0; i < num; ++i) {
        spawner->add(i * 720 / num, 50, 0.05 * i);
    }
    spawners.push_back(spawner);
    world.add_spawner(spawner);
}

void Monster::fire_right() {
    //const float r = 200;
    const float a = 50;
    const float b = .25;
    //const float th = deg2rad(30);
    const float av = deg2rad(200);

    string path = "cbullet.png";
    vector<Bullet*> bullets = {
        new FunBullet(path, 50, FPoint(292, 190) + pos,
            // theta = angle vel * time
            [a, b, av](float t) { return a * cos(av * t) * exp(b * av * t); },
            [a, b, av](float t) { return a * sin(av * t) * exp(b * av * t); })
    };
    fire_bullets(bullets);
}

